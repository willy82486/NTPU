var account=document.getElementById("index_account");
var btn=document.getElementById("index_btn");

btn.addEventListener("click",function(){
    if(account.value=="wei"){
        window.location="supply.html";
    }
    else if(account.value=="bbp"){
        window.location="process.html";
    }
    else if(account.value=="willy"){
        window.location="agent.html";
    }
    else{
        window.location="customer.html";
    }
})

