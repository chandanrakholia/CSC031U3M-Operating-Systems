if [ "$(python3 --version 2>&1 | awk '{print $2}')" != "3.11" ]; then
  echo "python 3.11 is not installed. Installing..."
  brew install python@3.11
else
  echo "python 3.11 is already installed."
fi


if [ ! "$(pip3 list | grep numpy)" ]; then
  echo "numpy is not installed. Installing."
  pip3 install numpy
else
  echo "numpy is already installed. Updating to the latest version"
  pip3 install numpy --upgrade
fi

echo "python version: $(python3 --version 2>&1 | awk '{print $2}')"