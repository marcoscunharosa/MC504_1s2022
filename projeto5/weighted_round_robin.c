#include <linux/syscalls.h>
#include <linux/cred.h>

int v_weights[65536] = {[0 ... 65535] = 10};

SYSCALL_DEFINE1(getuserweight, int, uid) {
	if(uid < -1 || uid > 65535){
		return  -EINVAL;
	}

	else if(uid == -1){
		uid = current_uid().val;
	}

	printk("O peso do usuário de id %d é %d\n", uid, v_weights[uid]);
	return v_weights[uid];
}

SYSCALL_DEFINE2(setuserweight, int, uid, int, weight) {
	if(uid < -1 || uid > 65535 || weight <= 0){
		return -EINVAL;
	}
	else if(uid == -1){
		uid = current_uid().val;
	}

	if(current_uid().val != 0) {
		return -EACCES;
	}

	v_weights[uid] = weight;
    	printk("O peso do usuário de id %d foi alterado para %d\n", uid, v_weights[uid]);
	return 0;
}
