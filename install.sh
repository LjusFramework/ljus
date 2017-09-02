git clone https://github.com/P-H-C/phc-winner-argon2.git includes/argon2
cd includes/argon2
make -j4
sudo make install

cd ../../

git clone https://github.com/jeremywohl/nacl includes/nacl
cd includes/nacl
./do

cd ../../

git clone https://github.com/oktal/pistache includes/pistache
cd includes/pistache
cmake .
make -j4
sudo make install

cd ../../

git clone https://github.com/tplgy/cppcodec includes/cppcodec
git clone https://github.com/nlohmann/json includes/json

cp includes/json/src/json.hpp ./json.hpp