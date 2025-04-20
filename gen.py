import random
import string

def random_word(length=32):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def generate_10mb_test(filename="test.htr"):
    target_size =  1024 * 1024  # 100MB
    written = 0
    keys = []

    with open(filename, "w") as f:
        while written < target_size * 0.5:
            key = random_word()
            value = random_word()
            keys.append(key)
            line = f"{key}\n{value}\n"
            f.write(line)
            written += len(line)

        f.write("\n")  

        for i in range(len(keys)):
            f.write(f"{keys[i]}\n") 
        for _ in range(len(keys) // 4):
            f.write(f"{random_word()}\n")  


generate_10mb_test()