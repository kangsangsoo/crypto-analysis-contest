# -*- coding:UTF-8
# https://crypto.stackexchange.com/questions/11743/scalar-multiplication-on-elliptic-curves
# Scalar Multiplication on Elliptic Curves

# Extended Euclidean algorithm
def extended_gcd(aa, bb):
   lastremainder, remainder = abs(aa), abs(bb)
   x, lastx, y, lasty = 0, 1, 1, 0
   while remainder:
       lastremainder, (quotient, remainder) = remainder, divmod(lastremainder, remainder)
       x, lastx = lastx - quotient*x, x
       y, lasty = lasty - quotient*y, y
   return lastremainder, lastx * (-1 if aa < 0 else 1), lasty * (-1 if bb < 0 else 1)

# calculate `modular inverse`
def modinv(a, m):
   g, x, y = extended_gcd(a, m)
   if g != 1:
       raise ValueError
   return x % m

# double function
def ecc_double(x1, y1, p, a):
   s = ((3*(x1**2) + a) * modinv(2*y1, p))%p
   x3 = (s**2 - x1 - x1)%p
   y3 = (s*(x1-x3) - y1)%p
   return (x3, y3)

# add function
def ecc_add(x1, y1, x2, y2, p, a):
   s = 0
   if (x1==x2):
       s = ((3*(x1**2) + a) * modinv(2*y1, p))%p
   else:
       s = ((y2-y1) * modinv(x2-x1, p))%p
   x3 = (s**2 - x1 - x2)%p
   y3 = (s*(x1 - x3) - y1)%p
   return (x3, y3)

def double_and_add(multi, generator, p, a):
   (x3, y3)=(0, 0)
   (x1, y1) = generator
   (x_tmp, y_tmp) = generator
   init = 0
   for i in str(bin(multi)[2:]):
       if (i=='1') and (init==0):
          init = 1
       elif (i=='1') and (init==1):
          (x3,y3) = ecc_double(x_tmp, y_tmp, p, a)
          (x3,y3) = ecc_add(x1, y1, x3, y3, p, a)
          (x_tmp, y_tmp) = (x3, y3)
       else:
          (x3, y3) = ecc_double(x_tmp, y_tmp, p, a)
          (x_tmp, y_tmp) = (x3, y3)
   return (x3, y3)

# values
p = 0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF
a = -3;
b = 0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B
Gx = 0x6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296
Gy = 0x4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5
Qx = 0xF44CD6277CED3F9CC2F29144CDBCFDC40F1BF556707ED8190E838D711A12EC03
Qy = 0x68B6FAF59BEC47A11D98800B4BE578CA4399B34EF94D6B602F5186D41B7430C9
s1 = 0x90A7F16EAFE3DB7923A07A6E8CF68F688100ABE3730A5416B37FA4BFBA7F5E22
s2 = 0x865BF221DD856B991EB6EF7EF1E0D263215FC8D7F2283A22C1F927ABDCC35B5B
r1 = 0xF42A3ADB78BF22D9AA571FDFB0C93B415C8B50719C25B23F6F77DC299C01F2D7
M1 = 0xE06554818E902B4BA339F066967C0000DA3FCDA4FD7EB4EF89C124FA78BDA419
M2 = 0x5D2D3CEB7ABE552344276D47D36A8175B7AEB250A9BF0BF00E850CD23ECF2E43
n = 0xFFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551

#list
k = [0,0,0,0]
d = [0,0,0,0]

# If (r, s) is  valid signature, then (r, -s) is also valid signature.
# There are 4 cases.

left = ( s1 + s2) %n
right = (M1 - M2) %n
k[0] = right * modinv(left, n) % n
left = (s1 * k[0] - M1) %n
invr1 = modinv(r1, n)
d[0] = (left * invr1) % n

left = ( -s1 + s2) %n
right = (M1 - M2) %n
k[1] = right * modinv(left, n) % n
left = (s1 * k[1] - M1) %n
invr1 = modinv(r1, n)
d[1] = (left * invr1) % n

left = ( s1 - s2) %n
right = (M1 - M2) %n
k[2] = right * modinv(left, n) % n
left = (s1 * k[2] - M1) %n
invr1 = modinv(r1, n)
d[2] = (left * invr1) % n

left = ( -s1 - s2) %n
right = (M1 - M2) %n
k[3] = right * modinv(left, n) % n
left = (s1 * k[3] - M1) %n
invr1 = modinv(r1, n)
d[3] = (left * invr1) % n

# Q = dg calculation
# If d is private key such that Q = dg  
for i in range(0,4):
   if double_and_add(d[i], (Gx,Gy), p, a) == (Qx, Qy):
      print("d[{0}] = {1}, k[{2}] = {3}".format(i, hex(d[i]).upper(), i, hex(k[i]).upper()))  



