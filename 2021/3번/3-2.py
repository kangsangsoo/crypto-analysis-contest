import hashlib
from os import putenv
from Crypto.Util.number import *
from ecdsa import ellipticcurve
from ecdsa.ecdsa import *
import json
from random import randrange

# lsh
from lsh import *
# lsh_digest.LSHDigest.digest(512, 512, b"123")


g = generator_256
n = g.order()


class Elliptic_curve_sign():
    def __init__(self):
        secret = randrange(1, n)
        self.pubkey = Public_key(g, g * secret)
        # 파라미터 확인하는 방법
        # print(self.pubkey.curve)
        # print(self.pubkey.generator.__dict__)
        self.privkey = Private_key(self.pubkey, secret)

    def lshHash(self, data):
        return lsh_digest.LSHDigest.digest(256, 256, data) # use lsh256

    def sign_msg(self, msg):
        hsh = self.lshHash(msg.encode())
        sig = self.privkey.sign(bytes_to_long(hsh), randrange(1, n))
        return {"msg": msg, "r": hex(sig.r), "s": hex(sig.s)}

    def verify(self, msg, sig_r, sig_s):
        hsh = bytes_to_long(self.lshHash(msg.encode()))
        sig_r = int(sig_r, 16)
        sig_s = int(sig_s, 16)
        sig = Signature(sig_r, sig_s)

        if self.pubkey.verifies(hsh, sig):
            return True
        else:
            return False

    def elliptic_curve_sign(self, your_input):
        your_input = json.loads(your_input)
        print(your_input)
        if 'option' not in your_input:
            return {"error": "You must send an option to this server"}

        elif your_input['option'] == 'sign_msg':
            signature = self.sign_msg(your_input['msg'])
            return signature

        elif your_input['option'] == 'verify':
            msg = your_input['msg']
            r = your_input['r']
            s = your_input['s']
            verified = self.verify(msg, r, s)
            if verified:
                return {"result": "Message verified"}
            else:
                return {"result": "Bad signature"}

        else:
            return {"error": "Decoding fail"}

Elliptic = Elliptic_curve_sign()
while(True):
    your_input = input(
'''
your input must be in form of Json
you have two option
1. sign_msg / You can sign your message 
ex) {"option": "sign_msg", "msg": "hello world"} 
2. verify / You can verify your message 
ex) {"option": "verify", "msg": "hello world", "r": "0x12345", "s": "0x123465"} 
<<< ''').replace("'", '"')
    print(Elliptic.elliptic_curve_sign((your_input)))


