# Use this by sourcing it in your script.

if [[ "$TRAVIS_BRANCH" == "master" && "$TRAVIS_PULL_REQUEST" == "false" ]] ; then
	git config --global user.name "QMK Bot"
	git config --global user.email "hello@qmk.fm"

	openssl aes-256-cbc -K $encrypted_b0ee987fd0fc_key -iv $encrypted_b0ee987fd0fc_iv -in secrets.tar.enc -out secrets.tar -d
	tar xvf secrets.tar

	chmod 600 id_rsa_qmk_firmware
	chmod 600 id_rsa_qmk.fm
	eval `ssh-agent -s`
	ssh-add id_rsa_qmk_firmware
fi
