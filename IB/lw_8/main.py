import tests.testEcdsa

if __name__ == "__main__":
    from ellipticcurve.ecdsa import Ecdsa
    from ellipticcurve.privateKey import PrivateKey

    # Generate new Keys
    privateKey = PrivateKey()
    publicKey = privateKey.publicKey()

    message = "My test message"

    # Generate Signature
    signature = Ecdsa.sign(message, privateKey)

     # To verify if the signature is valid
    print(Ecdsa.verify(message, signature, publicKey))

    message1 = "This is the right message"
    message2 = "This is the wrong message"

    signature = Ecdsa.sign(message1, privateKey)
    print("Сообщение: "+message1);
    print("Сообщение: "+message2);
    
    print(Ecdsa.verify(message1, signature, publicKey))
    print(Ecdsa.verify(message2, signature, publicKey))