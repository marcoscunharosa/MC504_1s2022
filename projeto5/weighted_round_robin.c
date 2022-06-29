#include <linux/syscalls.h>
#include <linux/user_namespace.h>
#include <errno.h>


int v_weights[65536];

int criar_vetor(int v_weights[65536]){
	int i;
	for (i=0; i < 65536; i++){
		v_weights[i] = 10;
	}
	return 0;
}

SYSCALL_DEFINE4(getuserweight, int, uid) {
	if(uid < -1 || uid > 65535){
		return  -EINVAL;
	}

	else if(uid == -1){
		uid = from_kuid_munged(current_user_ns(), current_uid());
	}

	printk("O peso do usuário de id %d é %d\n", uid, v_weights[uid]);
	return v_weights[uid];
}

SYSCALL_DEFINE5(setuserweight, int, uid, int, weight) {
	if(from_kuid_munged(current_user_ns(), current_uid()) != 0) {
		return -EACCES;
	}

	else if(uid < -1 || uid > 65535 || weight <= 0) {  
		return -EINVAL;
	}

	else if(uid == -1){
		uid = from_kuid_munged(current_user_ns(), current_uid());
	}

	v_weights[uid] = weight;
    	printk("O peso do usuário de id %d foi alterado para %d\n", uid, v_weights[uid]);
	return 0;
}
