from PIL import Image
from Crypto.Cipher import AES


# Function
def ECB(key, mode):
    try:
        fileTemp = open("temp.ppm", "rb")
        fileOut = open("ecbTemp.ppm", 'wb')
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
            if mode == 'E':
                fileOut.write(cipherBlock.encrypt(data))
            else:
                fileOut.write(cipherBlock.decrypt(data))
            data = fileTemp.read(16)

    finally:
        fileTemp.close()
        fileOut.close()


def CBC(key, iv, mode):
    try:
        fileTemp = open("temp.ppm", "rb")
        fileOut = open("cbcTemp.ppm", 'wb')
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
            if mode == 'E':
                for i, j in zip(data, iv):
                    temp.append((j ^ i) % 255)
                data = bytes(temp)
                code = cipherBlock.encrypt(data)
                fileOut.write(code)
                iv = code
            elif mode == 'D':
                code = cipherBlock.decrypt(data)
                for i, j in zip(code, iv):
                    temp.append((j ^ i) % 255)
                iv = data
                code = bytes(temp)
                fileOut.write(code)
            data = fileTemp.read(16)
    finally:
        fileTemp.close()
        fileOut.close()


while (True):
    fileName = input("請輸入檔案位置名稱 ：")
    print(fileName)
    encryptType = input("請輸入加密模式(ECB/CBC)：")
    handleMode = input("請輸入要加密or解密(E/D)")
    ppmPicture = 'temp.ppm'
    im = Image.open(fileName)
    im.save(ppmPicture)
    if (encryptType == 'ECB'):
        key = input("請輸入16位元key：")
        if (len(key) != 16):
            print("key長度錯誤，使用預設key (1231231231231231) ")
            ECB(b'1231231231231231', handleMode)
        else:
            ECB(bytes(key, encoding="utf8"), handleMode)
        im = Image.open('./ecbTemp.ppm')
        if handleMode == 'E':
            im.save('./ecbEncrypt.png')
        else :
            im.save('./ecbDecrypt.png')
        print("ECB加密完成")
    else:
        key = input("請輸入16位元key：")
        iv = input("請輸入16位元iv：")
        if (len(key) != 16):
            print("key長度錯誤，使用預設key (1231231231231231) ")
            key = "1231231231231231"
        if (len(iv) != 16):
            print("iv長度錯誤，使用預設iv (1f1f1f1f1f1f1f1f)")
            iv = "1f1f1f1f1f1f1f1f"
        CBC(bytes(key, encoding="utf8"), bytes(iv, encoding="utf8"), handleMode)
        im = Image.open('./cbcTemp.ppm')
        if handleMode == 'E':
            im.save('./cbcEncrypt.png')
        else :
            im.save('./cbcDecrypt.png')

        print("CBC加密完成")
