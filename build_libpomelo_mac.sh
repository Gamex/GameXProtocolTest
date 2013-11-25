rm -rf ./libpomelo/build
rm -rf ./libpomelo/deps/jansson/build
rm -rf ./libpomelo/deps/uv/build

xcodebuild -project ./libpomelo/deps/jansson/jansson.xcodeproj -arch x86_64
xcodebuild -project ./libpomelo/deps/uv/uv.xcodeproj -arch x86_64
xcodebuild -target "libpomelo" -project ./libpomelo/pomelo.xcodeproj -arch x86_64

rm -rf ./libpomelo/lib
mkdir ./libpomelo/lib

cp ./libpomelo/build/Default/libpomelo.a ./libpomelo/lib/libpomelo.a
cp ./libpomelo/deps/jansson/build/Default/libjansson.a ./libpomelo/lib/libjansson.a
cp ./libpomelo/deps/uv/build/Default/libuv.a ./libpomelo/lib/libuv.a

rm -rf ./libpomelo/build
rm -rf ./libpomelo/deps/jansson/build
rm -rf ./libpomelo/deps/uv/build


