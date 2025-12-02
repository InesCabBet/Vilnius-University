class HashSet{
   constructor(){
        this.loadFactor = 0.75;
        this.capacity = 16;
        this.size = 0;
        this.buckets = new Array(this.capacity);
    }
    hash(key){
        let hashCode = 0;

        const primeNumber = 31;
        for(let i = 0; i < key.length; i++) hashCode = (primeNumber * hashCode + key.charCodeAt(i)) % this.capacity;
        return hashCode;
    }
    set(key){
        const index = this.hash(key);
        
        if(!this.buckets[index]){
            this.buckets[index] = [key];
            this.size++;
            this.#checkLoadCapacity();
        }
        else{
            let isInBucket = false;
            for(const item of this.buckets[index]){
                if(item === key){
                    isInBucket = true;
                    break;
                }
            }
            if(!isInBucket){
                this.buckets[index].push(key);
                this.size++;
                this.#checkLoadCapacity();
            }
        }   
    }
    get(key){
        const index = this.hash(key);
        if(!this.buckets[index]) return null
        else{
            for(const item of this.buckets[index]){
                if(item === key) return item;
            }
            return null;
        }
    }
    has(key){
        const index = this.hash(key);
        if(!this.buckets[index]) return false;
        else{
            for(const item of this.buckets[index]){
                if(item === key) return true;
            }
            return false;
        }
    }
     remove(key){
        const index = this.hash(key);
        if(!this.buckets[index]) return false;
        else{
            const bucket = this.buckets[index];
            for(let i = 0; i < bucket.length; i++){
                if(bucket[i] === key){
                    bucket.splice(i, 1);
                    if(bucket.length === 0) this.buckets[index] = null;
                    this.size--;
                    return true;
                }
                
            }
            return false;
        }
    }
    length(){
        return this.size;
    }
    clear(){
        this.capacity = 16;
        this.size = 0;
        this.buckets = new Array(this.capacity);
    }
    keys(){
        const arr = [];
        for(const bucket of this.buckets){
            if(bucket){
                for(const element of bucket){
                    arr.push(element);
                }
            }
        }
        return arr;
    }
    #checkLoadCapacity(){
        if(this.size > this.loadFactor * this.capacity) this.#resize();
    }
    #resize(){
        this.capacity = this.capacity * 2;
        const oldBuckets = this.buckets;
        this.buckets = new Array(this.capacity);
        this.size = 0;

        for(let i = 0; i< oldBuckets.length; i++){
            if(oldBuckets[i]){
                for(const element of oldBuckets[i]){
                    this.set(element);
                }
            }
        }
    }
}