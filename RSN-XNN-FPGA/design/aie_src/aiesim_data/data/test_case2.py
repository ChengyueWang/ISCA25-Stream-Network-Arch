import numpy as np
from write_file import mat2file

# 32x16x32 1 iteration k_iter=1  data increase by 1

def main():

    # a = np.arange(1, 32*16+1)
    # b = np.arange(1, 32*16+1) 

    a = np.ones(32*32)
    b = np.ones(32*32)

    # for i in range(32):
    #     a[i] = i

    c = np.matmul(a.reshape(32,32), b.reshape(32,32))
    c_1 = np.matmul(a.reshape(32,32), b.reshape(32,32)) + c
    c_2 = np.matmul(a.reshape(32,32), b.reshape(32,32)) + c_1
    c = np.matmul(a.reshape(32,32), b.reshape(32,32)) + c_2

    # change layout
    a_temp = np.ones(32*32).astype(np.float32)
    for i in range(16):
        for j in range(32):
            for k in range(2):
                a_temp[i*32*2+j*2+k] = a[(i*2+k)*32+j]
    a = a_temp.reshape((32,32))

    b_temp = np.ones(32*32).astype(np.float32)
    for i in range(4):
        for j in range(32):
            for k in range(8):
                b_temp[i*32*8+j*8+k] = b[j*32+i*8+k]
    b = b_temp.reshape((32,32))
    
    c = c.reshape((32*32))
    c_temp = np.ones(32*32).astype(np.float32)
    for i in range(4):
        for j in range(32):
            for k in range(8):
                c_temp[i*32*8+j*8+k] = c[j*32+i*8+k]
    c = c_temp.reshape((32,32))


    mat2file(a, "inputa_float.txt")
    mat2file(b, "inputb_float.txt")
    mat2file(c, "ref_outputc_float.txt") #, sn=True)



if __name__ == '__main__':
    main()
