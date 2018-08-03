build:
	cd hello; node-gyp configure && node-gyp build
	cd promise; node-gyp configure && node-gyp build

run-hello:
	cd hello; node hello.js

run-promise:
	cd promise; node promise.js
