int traffik_lys(node, state, count[1]){
	switch(state){
	case 1:
		if (node.d1 == green)
			count[0]--;
			return 1;
		else
			return 0;
	break;
	case 2;
		if (node.d2 == green)
			count[0]--;
			return 1;
		else
			return 0;	
	break;
	}
}