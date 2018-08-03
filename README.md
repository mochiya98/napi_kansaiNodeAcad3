# 関西node学園 3時限目 N-APIサンプル
> みんなN-API使おう！  

![preview](https://github.com/mochiya98/napi_kansaiNodeAcad3/raw/media/hello.png)  

## node-gyp installation
[詳細はnode-gypのREADME参照のこと](https://github.com/nodejs/node-gyp)  
python2.7xとかxcode/gcc,make/vc++とか入れた上で  
```
sudo npm i -g node-gyp
```

## build
```sh
git clone --depth 1 git@github.com:mochiya98/napi_kansaiNodeAcad3.git
cd napi_kansaiNodeAcad3
make build
```

## build(without make)
```sh
cd hello
node-gyp configure && node-gyp build
cd ..\promise
node-gyp configure && node-gyp build
```
