
function sleep(n){
    return new Promise((r,x)=>{
        setTimeout(r, n);
    })
}

async function setTest(){
	var itung = 0;
    while(true){
        await sleep(1000);
        console.log("ini test aja ya");
		itung++;
		
		
    }
}


setTest();