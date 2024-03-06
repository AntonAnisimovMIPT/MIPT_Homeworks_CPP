#include <iostream>
#include <string>
#include <random>
#include <set>
#include <map>

unsigned int RSHash(const char* str, unsigned int length)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
   unsigned int hash = length;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }

   return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}

auto RandomStrings(std::size_t number_strings) {
    const std::string AcceptableSymbols = "abcdefghijklmnopqrstuvwxyz";

    std::random_device device; // note: make seed only once
    std::mt19937 engine(device());
    std::uniform_int_distribution distribution(0, static_cast<int>(std::size(AcceptableSymbols)) - 1); // note: [a; b)

    std::set<std::string> Randoms;
    std::string randstr = "";

    for (size_t i = 0; i < number_strings; ++i)
    {
        for (size_t i = 0; i < 10; ++i)
        {
            randstr += AcceptableSymbols[distribution(engine)];
        }
        if (Randoms.find(randstr) == Randoms.end()) {
            Randoms.insert(randstr);
        }
        randstr = "";
    }
    
    return Randoms;

}

void Hashes_Research(const std::vector<std::string>& strings, const std::string& functionName, unsigned int (*hashFunction)(const char*, unsigned int)) {
    
    std::set<int> hashes;
    auto counter = 0;

    for (const auto& str : strings) {
        auto hash = hashFunction(str.c_str(), str.length());
        if (hashes.count(hash) > 0) {
            ++counter;
        }
        hashes.insert(hash);
    }

    std::cout << "Hash-function: " << functionName << "\n";
    std::cout << "Number collisions: " << counter  << "\n";
}


int main() {

    size_t N = 100000;
    std::set<std::string> RandomsSet;

    std::vector<std::string> RandomsVector;

    while (N <= 2000000)
    {
        std::cout << "N: " << N << "\n";
        RandomsSet = RandomStrings(N);
        std::vector<std::string>RandomsVector(RandomsSet.begin(), RandomsSet.end());

        Hashes_Research(RandomsVector, "RSHash", RSHash);
        Hashes_Research(RandomsVector, "JSHash", JSHash);
        Hashes_Research(RandomsVector, "PJWHash", PJWHash);
        Hashes_Research(RandomsVector, "ELFHash", ELFHash);
        Hashes_Research(RandomsVector, "BKDRHash", BKDRHash);
        Hashes_Research(RandomsVector, "SDBMHash", SDBMHash);
        Hashes_Research(RandomsVector, "DJBHash", DJBHash);
        Hashes_Research(RandomsVector, "DEKHash", DEKHash);
        Hashes_Research(RandomsVector, "APHash", APHash);

        N += 100000;

    }

    

    
   /*
    for (const auto& elem : Randoms) {
        std::cout << elem << "\n";
    }
*/
    
/*
    Hash_Research<RSHash>(RandomStrings);
    Hash_Research<JSHash>(RandomStrings);
    Hash_Research<PJWHash>(RandomStrings);
    Hash_Research<ELFHash>(RandomStrings);
    Hash_Research<BKDRHash>(RandomStrings);
    Hash_Research<SDBMHash>(RandomStrings);
    Hash_Research<DJBHash>(RandomStrings);
    Hash_Research<DEKHash>(RandomStrings);
    Hash_Research<APHash>(RandomStrings);


*/
    
}