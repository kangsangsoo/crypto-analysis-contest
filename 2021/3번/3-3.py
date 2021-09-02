import hashlib
from Crypto.Util.number import *
from ecdsa import ellipticcurve
from ecdsa.ecdsa import *
import json
from random import randrange
from lsh import *
import pickle

# global variables
g = generator_256
n = g.order()
tx_list = []
wallet_list = []

class Pubkey:
    # G, P, Q
    # p256r1은 동일하기 떄문에 
    # Q만
    # Q = Gx

    Q_x = None
    Q_y = None
    Q_z = None

    def __init__(self, Q_x, Q_y, Q_z):
        self.Q_x = Q_x
        self.Q_y = Q_y
        self.Q_z = Q_z

class Opcode:
    # 가능한 명령어
    # dup: 스택 제일 위 값을 복사
    # hash: 스택 제일 위 값을 해시 
    # equal: 2개 팝해서 같은지 확인
    # push: push 명령어 다음에 있는 것을 스택에 push
    # checksig: 2개를 팝해서 서명 검증 결과를 스택에 push
    opcode = None

    def __init__(self, li):
        self.opcode = li

    # 아직 해야함..

class scriptPubkey:
    opcode = None
    pubkey_hash = None

    def __init__(self, pubkey_hash):
        self.pubkey_hash = pubkey_hash
        # 자동 생성
        self.opcode = Opcode(["dup", "hash", "push", pubkey_hash, "equal", "checksig"])

class scriptSig:
    sig = None # {'msg': 130350994118399246426527930520790875261974487327230605603026547952052364385201, 'r': '0xb2b3b1bfc0e4aa21796ae62d2da642f15f5c42d01846e8e82ea743ac276b7117', 's': '0x740c7918aba03985679fa2d50799bb23c92f19376a15baa8303b96e84fbee2df'}
    pubkey = None # Pubkey 클래스
    opcode = None

    def __init__(self, sig, pubkey):
        self.sig = sig # json
        self.pubkey = pubkey
        # 자동 생성
        self.opcode = Opcode(["push", sig, "push", pubkey])


class TX:
    tx_id = None
    in_utxo = None
    in_wallet_id = None
    in_addr = None
    in_value = None
    in_pub = None    # scriptPubkey
    in_sig = None    # scriptSig
    out_wallet_id = None
    out_addr = None
    out_value = None
    out_pub = None   # scriptPubkey
    
    def __init__(self, tx_id, in_utxo, in_wallet_id, in_addr, in_value, in_pub, in_sig, out_wallet_id, out_addr, out_value, out_pub):
        self.tx_id = tx_id
        self.in_utxo = in_utxo
        self.in_wallet_id = in_wallet_id
        self.in_addr = in_addr
        self.in_value = in_value
        self.in_pub = in_pub
        self.in_sig = in_sig
        self.out_wallet_id = out_wallet_id
        self.out_addr = out_addr
        self.out_value = out_value
        self.out_pub = out_pub

class Wallet:
    id = None
    pubkey = None
    prikey = None

    def __init__(self, id, pubkey, prikey):
        self.id = id
        self.pubkey = pubkey
        self.prikey = prikey

def createWallet():
    global n, wallet_list
    id = len(wallet_list)
    secret = randrange(1, n)
    pubkey = Public_key(g, g * secret)
    prikey = Private_key(pubkey, secret)
    wallet_list.append(Wallet(id, pubkey, prikey))
    print(":: Create Wallet ::\nid: %d\npubkey(Qx, Qy, Qz): %d, %d, %d\nprikey: %d" % (id, pubkey.point.__dict__['_PointJacobi__x'], pubkey.point.__dict__['_PointJacobi__y'], pubkey.point.__dict__['_PointJacobi__z'], prikey.__dict__['secret_multiplier'] ))

def listWallet():
    global wallet_list

    print("::Wallet List::")
    for i in range(1, len(wallet_list)):
        print("idx: %d, pubkey(Qx, Qy, Qz): %d, %d, %d"%(i, wallet_list[i].pubkey.point.__dict__['_PointJacobi__x'], wallet_list[i].pubkey.point.__dict__['_PointJacobi__y'], wallet_list[i].pubkey.point.__dict__['_PointJacobi__z']))

def createPubkeyByIdx(wallet_idx):
    global wallet_list
    pubkey = Pubkey(wallet_list[wallet_idx].pubkey.point.__dict__['_PointJacobi__x'], wallet_list[wallet_idx].pubkey.point.__dict__['_PointJacobi__y'], wallet_list[wallet_idx].pubkey.point.__dict__['_PointJacobi__z'])
    digest = lsh_digest.LSHDigest.digest(256, 256, str(pubkey.Q_x).encode())
    digest = lsh_digest.LSHDigest.digest(256, 256, str(pubkey.Q_y).encode()+digest)
    digest = lsh_digest.LSHDigest.digest(256, 256, str(pubkey.Q_z).encode()+digest)
    return scriptPubkey(bytes_to_long(digest))

def createPubkey(Qx, Qy, Qz):
    global wallet_list
    return Pubkey(Qx, Qy, Qz)

def listTransaction():
    global tx_list
    print(":: tx_list ::")
    
    for i in range(len(tx_list)):
        # tx_id = None
        # in_utxo = None
        # in_wallet_id = None
        # in_addr = None
        # in_value = None
        # in_pub = None    # scriptPubkey
        # in_sig = None    # scriptSig
        # out_addr = None
        # out_value = None
        # out_pub = None   # scriptPubkey
        print("-"*80)
        print("tx_id: %d, in_utxo: %d, in_wallet_id: %d, in_addr: %d, in_value: %d"%(tx_list[i].tx_id, tx_list[i].in_utxo, tx_list[i].in_wallet_id, tx_list[i].in_addr, tx_list[i].in_value))
        print("in_pub: ", end="")
        print(tx_list[i].in_pub.opcode.__dict__)
        print("in_sig: ", end="")
        print(tx_list[i].in_sig.opcode.__dict__['opcode'][:-1], end="")
        if type(tx_list[i].in_sig.opcode.__dict__['opcode'][-1]) == int:
            print()
        else:
            print(tx_list[i].in_sig.opcode.__dict__['opcode'][-1].__dict__)
        print("out_wallet_id: %d, out_addr: %d, out_value: %d" %(tx_list[i].out_wallet_id, tx_list[i].out_addr, tx_list[i].out_value))
        print("out_pub: ", end="")
        print(tx_list[i].out_pub.opcode.__dict__)
        print("-"*80)


def lshHash(data):
        return lsh_digest.LSHDigest.digest(256, 256, data) # use lsh256

def p256r1_sign_msg(msg, id):
    global wallet_list
    privkey = wallet_list[id].prikey
    hsh = lshHash(long_to_bytes(msg))
    sig = privkey.sign(bytes_to_long(hsh), randrange(1, n))
    return {"msg": msg, "r": str(sig.r), "s": str(sig.s)}

def verify(msg, sig_r, sig_s, pubkey_owner_wallet_id):
    global wallet_list


    hsh = bytes_to_long(lshHash(long_to_bytes(msg)))
    sig_r = int(sig_r)
    sig_s = int(sig_s)
    sig = Signature(sig_r, sig_s)

    # genesis wallet에 point만 바꾸어 키로 사용함.
    pubkey = wallet_list[pubkey_owner_wallet_id].pubkey
    
    if pubkey.verifies(hsh, sig):
        return True
    else:
        return False

class Stack():
    def __init__(self):
        self.stack = []
    
    def push(self, data):
        self.stack.append(data)
    
    def pop(self):
        if self.isEmpty():
            print("stack is empty")
            return None
        else :
            return self.stack.pop()

    def isEmpty(self):
        if len(self.stack) == 0:
            return True
        return False

    def print(self):
        print(self.stack)

def stackProcessor(commands):
    global wallet_list
    print()
    stack = Stack()

    for i in range(len(commands)):

        # dup: 스택 제일 위 값을 복사
        # hash: 스택 제일 위 값을 해시 
        # equal: 2개 팝해서 같은지 확인
        # push: push 명령어 다음에 있는 것을 스택에 push
        # checksig: 2개를 팝해서 서명 검증 결과를 스택에 push

        # opcode인지 값인지 체크
        #  "push", sig, "push", pubkey "dup", "hash", "push", pubkey_hash, "equal", "checksig"])
        if commands[i] == 'push':
            stack.print()
            stack.push(commands[i+1])

        if commands[i] == 'hash':
            stack.print()
            value = stack.pop()

            # PubkeyHash는 아래처럼 만들기로 약속
            digest = lsh_digest.LSHDigest.digest(256, 256, long_to_bytes(value.Q_x))
            digest = lsh_digest.LSHDigest.digest(256, 256, long_to_bytes(value.Q_y)+digest)
            digest = lsh_digest.LSHDigest.digest(256, 256, long_to_bytes(value.Q_z)+digest)
            stack.push(bytes_to_long(digest))

        if commands[i] == 'equal':
            stack.print()

            value1 = stack.pop()
            value2 = stack.pop()

            if value1 == value2:
                print('equal')
            else:
                print("not equal => invalid transaction")
                return

        if commands[i] == 'dup':
            stack.print()
            dup = stack.pop()
            stack.push(dup)
            stack.push(dup)

        if commands[i] == 'checksig':
            # 서명 검증
            stack.print()
            pubkey = stack.pop()
            sig = stack.pop()

            #genesis wallet
            id = 0

            wallet_list[0].pubkey.point._PointJacobi__x = pubkey.Q_x
            wallet_list[0].pubkey.point._PointJacobi__y = pubkey.Q_y
            wallet_list[0].pubkey.point._PointJacobi__z = pubkey.Q_z

            
            # sig에서 msg, r, s 분리
            
            sig = json.loads(sig)
            msg = sig['msg']
            r = sig['r']
            s = sig['s']  

            stack.push(verify(msg, r, s, id))                 

    stack.print()
    
    if stack.pop() == True:
        print("Transaction is valid")
    else:
        print("Transaction is invalid")
        

# Make genesis tx
# genesis_wallet
createWallet()

# 채굴자 개념이 없기 때문에.. 
# genesis_tx  
# genesis_wallet과 genesis_tx에 대한 접근 X
genesis_tx = TX(tx_id = 0, in_utxo = 0, in_wallet_id = 0, in_addr = 0, in_value = 1000, in_pub = scriptPubkey(0), in_sig = scriptSig(0, 0), out_wallet_id = 0, out_addr = 0, out_value = 1000, out_pub = createPubkeyByIdx(0))
tx_list.append(genesis_tx)


def intro():
    print('''
Welcome real estate online trade platform!
We provide three menus.
1. Create Wallet
2. List Wallet
3. Create Transaction
4. List Transaction
5. Verify Transcaction
6. Get pubkeyHashValue
7. Get Signature
8. Exit''')

while True:
    intro()
    menu = input("<<< ")

    if menu == '1':
        print()
        createWallet()

    elif menu == '2':
        print()
        listWallet()

    elif menu == '3':
        print()
        print("We need in_utxo, in_addr, in_value, in_pub, in_sig, out_addr, out_value, out_pub")
        tx_id = len(tx_list)
        in_utxo = int(input("in_utxo (integer) <<< "))
        in_wallet_id = int(input("in_wallet_id (integer) <<< "))
        in_addr = int(input("in_addr (integer) <<< "))
        in_value = int(input("in_value (integer) <<< "))
        in_pub = int(input("in_pub (integer) only input pubKeyHashValue. We automatically construct opcode <<< "))
        pubkey_in_sig_Qx = int(input("your pubkey in in_sig (integer)\nQx <<< "))
        pubkey_in_sig_Qy = int(input("Qy <<< "))
        pubkey_in_sig_Qz = int(input("Qz <<< "))
        sig_in_sig = input("signature in in_sig (JSON) ex) {'msg': 130350994118399246426527930520790875261974487327230605603026547952052364385201, 'r': '651616516516513515135165165161651651465165165165165165', 's': '46545465465465454654685465465465465465465465'} We automatically construct opcode <<< ")
        out_wallet_id = int(input("out_wallet_id (integer) <<< "))
        out_addr = int(input("out_addr (integer) <<< "))
        out_value = int(input("out_value (integer) <<< "))
        out_pub = int(input("out_pub (integer) only input pubKeyHashValue. We automatically construct opcode <<< "))
        
        
        # sig_in_sig single quote => double quote, json.loads 하기 위해서
        sig_in_sig = sig_in_sig.replace("'", '"')

        # utxo_id 검증 말고는 유효한지 확인하지 않음. 

        if in_utxo >= len(tx_list):
            print("Invalid utxo id")
            break

        scriptsig = scriptSig(sig_in_sig, Pubkey(pubkey_in_sig_Qx, pubkey_in_sig_Qy, pubkey_in_sig_Qz))
        outpub = scriptPubkey(out_pub)
        tx = TX(tx_id, in_utxo, in_wallet_id, in_addr, in_value, tx_list[in_utxo].out_pub, scriptsig, out_wallet_id, out_addr, out_value, outpub)
        tx_list.append(tx)

    elif menu == '4':
        print()
        listTransaction()

    elif menu == '5':
        print()
        print(":: Verify Transaction ::")
        print("Input tx_id you want to verify")
        tx_id = int(input("tx_id <<< "))

        # 존재하는 tx인지 확인

        if tx_id >= len(tx_list):
            print("Invalid tx_id")
            break
        if tx_id == 0:
            print("genesis tx cannot be verfied")
            break

        # tx_id 검증은 
        # 검증할 tx에서
        # in_scriptSig와 in_scirptPubkey를 스택 프로세스에서 돌리면 된다.
        
        commands = tx_list[tx_id].in_sig.opcode.opcode + tx_list[tx_id].in_pub.opcode.opcode
        stackProcessor(commands)



    elif menu == '6':
        print()
        print(":: Create PubkeyHashValue ::")
        print("Input Qx, Qy, Qz")
        Qx = int(input("Qx (integer) <<< "))
        Qy = int(input("Qy (integer) <<< "))
        Qz = int(input("Qz (integer) <<< "))
        # PubkeyHash는 아래처럼 만들기로 약속
        digest = lsh_digest.LSHDigest.digest(256, 256, long_to_bytes(Qx))
        digest = lsh_digest.LSHDigest.digest(256, 256, long_to_bytes(Qy)+digest)
        digest = lsh_digest.LSHDigest.digest(256, 256, long_to_bytes(Qz)+digest)
        print("PubkeyHashValue: ", end="")
        print(bytes_to_long(digest))



    elif menu == '7':
        print()
        print(":: Create Signature ::")
        print("We give you sign(utxo_hash + pubkeyHashValue in utxo + pubkeyHashValue in your_tx)")
        print("So input tx_id that is utxo, pubkeyHashValue in your_tx, your prikey")
        utxo_id = int(input("tx_id(utxo_id) <<< "))
        pubkeyHashValue = int(input("pubkeyHashValue in your_tx <<< "))
        prikey = int(input("prikey <<< "))
        wallet_id = int(input("wallet id <<< "))

        # utxo_id 유효한지 확인
        if utxo_id >= len(tx_list):
            print("Invlaid utxo_id")
            break

        # prikey와 wallet id와 일치하면 거기서 prikey랑 pubkey 끌어 쓰기
        if prikey != wallet_list[wallet_id].prikey.__dict__['secret_multiplier']:
            print("Invalid prikey")
            break

        # utxo 전체를 해시할 때는 pickle.dumps를 사용해 TX를 바이트화 해서 진행 
        msg = bytes_to_long(lsh_digest.LSHDigest.digest(256, 256, pickle.dumps(tx_list[utxo_id]))) + tx_list[utxo_id].out_pub.pubkey_hash + pubkeyHashValue

        print(p256r1_sign_msg(msg, wallet_id))

    elif menu == '8':
        print("Good bye~")
        break

    else:
        print("Invalid Input")