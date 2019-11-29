from PIL import Image
from Crypto.Cipher import AES

#Function
def ECB(key):
    try:
        fileTemp    = open("temp.ppm", "rb")
        fileOut     = open("ecbTemp.ppm", 'wb')
        cipherBlock = AES.new(key, AES.MODE_ECB)
        for i in range(3):
           data = fileTemp.readline()
           fileOut.write(data)
        data = fileTemp.read(16)

        while data:
            if len(data) < 16:
                counter = 16 - len(data)
                for i in range(counter):
                    data += bytes([0])

         
            fileOut.write(cipherBlock.encrypt(data))
            data = fileTemp.read(16)

    finally:
        fileTemp.close()
        fileOut.close()

def CBC(key, iv):
    try:
         fileTemp    = open("temp.ppm", "rb")
         fileOut     = open("cbcTemp.ppm", 'wb')
         cipherBlock = AES.new(key, AES.MODE_ECB)
         for i in range(3):
           data = fileTemp.readline()
           fileOut.write(data)
         data = fileTemp.read(16)

         while data:
                if len(data) < 16:
                    counter = 16 - len(data)
                    for i in range(counter):
                         data += bytes([0])
                temp = []

                for i,j in zip(data,iv):
                    temp.append((j ^ i) %255)
                data = bytes(temp)
                code = cipherBlock.encrypt(data)
                fileOut.write(code)
                iv = code
                data = fileTemp.read(16)
    finally:
        fileTemp.close()
        fileOut.close()

while(True):
    fileName = input("請輸入檔案位置名稱(按ENTER使用預設圖片) ：")
    if(fileName == ""):
        fileName = "test.png"
        print('使用預設圖片')
    encryptType = input("請輸入加密模式(ECB/CBC)(按ENTER兩者都執行)：")
    ppmPicture = 'temp.ppm'
    im = Image.open(fileName)
    im.save(ppmPicture)
    if(encryptType == 'ECB'):
        key = input("請輸入16位元key：")
        if(len(key) != 16):
            print("key長度錯誤，使用預設key (1231231231231231) ")
            ECB(b'1231231231231231')
        else:
            ECB(bytes(key,encoding = "utf8"))
        im = Image.open('./ecbTemp.ppm')
        im.save('./ecbEncrypt.png')
        print("ECB加密完成")
    elif(encryptType == 'CBC'):
        key = input("請輸入16位元key：")
        iv  = input("請輸入16位元iv：")
        if(len(key) != 16):
            print("key長度錯誤，使用預設key (1231231231231231) ")
            key = "1231231231231231"
        if(len(iv)!=16):
            print("iv長度錯誤，使用預設iv (1f1f1f1f1f1f1f1f)")
            iv = "1f1f1f1f1f1f1f1f"
        CBC(bytes(key,encoding = "utf8"),bytes(iv,encoding = "utf8"))
        im = Image.open('./cbcTemp.ppm')
        im.save('./cbcEncrypt.png')
        print("CBC加密完成")
    else:
        ECB(b'1231231231231231')
        CBC(b'1231231231231231',b'1f1f1f1f1f1f1f1f')
        im = Image.open('./cbcTemp.ppm')
        im.save('./cbcEncrypt.png')
        im = Image.open('./ecbTemp.ppm')
        im.save('./ecbEncrypt.png')
        print('加密完成')