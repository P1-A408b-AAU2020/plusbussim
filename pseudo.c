
void traffic_lights(){
    int counter = 0;
    if(node.d1 == green && counter == 0){
        node.d1 = red;
        counter = 30;
    } else if(node.d1 == red && counter == 0){
        node.d1 = green;
        counter = 30;        
    }
    if(node.d2 == green && counter == 0){
        node.d2 = red;
        counter = 30;
    } else if(node.d2 == red && counter == 0){
        node.d2 = green;
        counter = 30;        
    }
}

int check_state(node, state){
	switch(state){
	case 1:
		if (node.d1 == green){
            if(check_light() == 1)
                counter += 10;
            counter--;
        }else{
            if(check_light() == 1)
                counter = 5;
            counter--;
        }
	break;
	case 2:
		if (node.d2 == green){
            if(check_light() == 1)
                counter += 5;
        }else{
            if(check_light() == 0)
                counter = 5;
        }
	break;
	}
}

int check_light(actors, link, counter){
    int i, run = 0;
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        if(actor[i].is_plusbus == 1 && link[10] == actor[i])
            run = 1;
    }
    return run;
}
