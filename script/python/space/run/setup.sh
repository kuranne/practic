#--- Python Setup ---#
[[ $(command -v python3) ]] || { echo "Can't execute python3"; exit 1; }

python3 -m venv .venv
source ./.venv/bin/activate
pip install -r ./requirements.txt

#--- Compiler? ---#
pyinstaller --onefile run.py

# Clear & Clean
mv ./dist/run .
rm -rf ./build/ ./dist/ run.spec
