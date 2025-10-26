class HashTable:
    #Constructor, default size 100
    #Initializing a list of empty lists(buckets) to store [id, package]'s
    def __init__(self, size=100):
        self.table_size = size
        self.buckets = [[] for _ in range(size)]

    #Hashes the given id into a hash_index, find the specified bucket
    #If the ID is already in the bucket insert the package, otherwise, if the ID is not in the bucket add a list into the list with the id and package([id, package])
    #Return true when insertion occurs
    def insert(self, id, package):
        #Generate hash_index from id to find needed bucket
        hash_index = hash(id) % len(self.buckets)
        bucket = self.buckets[hash_index]
        
        #Check to see if the id exists, if it does, add the package.
        for pkg in bucket:
            if pkg[0] == id:
                pkg[1] = package
                return True
        
        #If the ID doesn't exist, add id and package to bucket
        bucket.append([id, package])
        return True

    #Hashes the given id into a hash_index, find the specified bucket
    #If the ID is found, return the package, if not, return None
    def lookup(self, id):
        #Generate hash_index from id to find needed bucket
        hash_index = hash(id) % len(self.buckets)
        bucket = self.buckets[hash_index]
        
        #Check to see if id is in the bucket, if it does, return the package
        for package in bucket:
            if package[0] == id:
                return package[1]
        
        #If the ID does not exist, return None
        return None

    #Hashes the given id into a hash_index, find the specified bucket
    #If the ID is found, remove the package and return true, if the ID is not found return false
    def remove(self, id):
        #Generate hash_index from id to find needed bucket
        hash_index = hash(id) % len(self.buckets)
        bucket = self.buckets[hash_index]
        
        #Check to see if id is in the bucket, if it does, remove the package
        for package in bucket:
            if package[0] == id:
                bucket.remove(package)
                return True
        
        #If the ID does not exist, return false
        return False
