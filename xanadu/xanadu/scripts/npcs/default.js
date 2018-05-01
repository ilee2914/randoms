function start() {
	cm.sendNext("hello");
}

function action(mode, type, selection) {
	cm.sendOk("hola");
	cm.dispose();
}