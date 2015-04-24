echo "Adding apt repositories."
sudo add-apt-repository -y ppa:terry.guo/gcc-arm-embedded

echo "Installing gcc_arm software"
sudo apt-get update
sudo apt-get install -y gcc-arm-none-eabi
