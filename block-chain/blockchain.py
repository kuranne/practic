import hashlib
import json
import time

class Block:
    def __init__(self, index, previous_hash, timestamp, data, nonce=0):
        self.index = index
        self.previous_hash = previous_hash
        self.timestamp = timestamp
        self.data = data
        self.nonce = nonce
        self.hash = self.calculate_hash()

    def calculate_hash(self):
        # Exclude 'hash' itself from the calculation
        block_dict = self.__dict__.copy()
        if 'hash' in block_dict:
            del block_dict['hash']
        block_string = json.dumps(block_dict, sort_keys=True)
        return hashlib.sha256(block_string.encode()).hexdigest()

class Blockchain:
    def __init__(self):
        self.chain = [self.create_genesis_block()]

    def create_genesis_block(self):
        return Block(0, "0", time.time(), "Genesis Block")

    def get_latest_block(self):
        return self.chain[-1]

    def add_block(self, new_block):
        new_block.previous_hash = self.get_latest_block().hash
        # Re-calculate hash after updating previous_hash
        new_block.hash = new_block.calculate_hash()
        self.chain.append(new_block)

    def is_chain_valid(self):
        for i in range(1, len(self.chain)):
            current = self.chain[i]
            previous = self.chain[i-1]

            if current.hash != current.calculate_hash():
                return False
            if current.previous_hash != previous.hash:
                return False
        return True

# Example usage:
if __name__ == "__main__":
    my_blockchain = Blockchain()
    
    print("Mining block 1...")
    my_blockchain.add_block(Block(1, "", time.time(), "Transaction Data: Alice sends 1 BTC to Bob"))
    
    print("Mining block 2...")
    my_blockchain.add_block(Block(2, "", time.time(), "Transaction Data: Bob sends 0.5 BTC to Charlie"))

    for block in my_blockchain.chain:
        print(f"Index: {block.index}")
        print(f"Hash: {block.hash}")
        print(f"Previous Hash: {block.previous_hash}")
        print(f"Data: {block.data}")
        print("-" * 20)

    print(f"Is blockchain valid? {my_blockchain.is_chain_valid()}")
