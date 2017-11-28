# Raspberry pi	3	buzzcoin wallet compilation manual	
## This manual is inteded for raspberry pi 3 with a raspbian operating system installed.
1. updates the list of available packages and their versions
```
sudo apt-get update
```
2. Installs newest versions of the packages you have.
```
sudo apt-get upgrade
```
Confirm with ‘Y’

3. Install all dependancies	
```
sudo apt-get install libboost-all-dev libssl-dev build-essential libdb++-dev libqrencode-dev libqt4-dev libminiupnpc-dev 
qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools build-essential libboost-dev libboostsystem-dev 
libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libminiupnpc-dev
```
Confirm with ‘Y’

4. Change your directory to Documents
```
cd /home/pi/Documents
git clone https://github.com/buzzcoin-project/BUZZ.git
```
5. Compile it
```
cd BUZZ
qmake
make
```
6. install boostrap files

execute	buzzcoin-qt
```
./buzzcoin-qt
```
this will create /home/pi/.buzzcoin

kill the wallet
```
ps | grep -i buzzcoin
kill x
```
download the bootstrap and copy it to /home/pi/.buzzcoin

7. Start the	wallet

Wait till it gets synced and enjoy staking!
