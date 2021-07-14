```bash


emcmake cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=`pwd`/../install -DBUILD_WASM=ON ..

mkdir buildwasm && cd buildwasm
emcmake cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../install -DBUILD_WASM=ON ..
make openvdb_shared
```

python3 SimpleHTTPServer.py

## enable pthreads in FF and chrome

chrome73: https://www.google.com/chrome/
1. download ubuntu binary:
2. unpack .dep: pkg -x google-chrome-stable_current_amd64.deb ./chrome
3. run executable: ./opt/google/chrome/chrome
4. set flags for "webassembly" using "chrome://flags/"

firefox nightly:
1. download ubuntu binary: https://www.mozilla.org/de/firefox/channel/desktop/
2. unpack
3. add line in "./defaults/pref/channel-prefs.js" -> pref("javascript.options.shared_memory", true);
4. run