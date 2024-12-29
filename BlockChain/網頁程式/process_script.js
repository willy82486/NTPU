if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);

} else {
    // set the provider you want from Web3.providers
    web3 = new Web3(new Web3.providers.HttpProvider("http://127.0.0.1:8545"));
	console.log("Using http provider");
}


// Previous if/else statement removed for brevity

web3.eth.defaultAccount = '0xFEeC85D2879321051032a3f5b62d1246C53Fcc1A';
console.log(web3.eth.defaultAccount);

var address = '0x194817C69C59A59C71b41A3791cCD9F5144A0476';
var abi = [
	{
		"inputs": [
			{
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			},
			{
				"internalType": "string",
				"name": "Good_Name",
				"type": "string"
			},
			{
				"internalType": "string",
				"name": "Proposed_Method",
				"type": "string"
			},
			{
				"internalType": "uint256",
				"name": "Customer_Service",
				"type": "uint256"
			},
			{
				"internalType": "uint256",
				"name": "Price",
				"type": "uint256"
			}
		],
		"name": "Agent_Work",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "address",
				"name": "tmp_Address",
				"type": "address"
			}
		],
		"name": "Allow_Asking",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "enum Good_Resume.Company",
				"name": "tmp_Choose",
				"type": "uint8"
			},
			{
				"internalType": "string",
				"name": "tmp_Company_Address",
				"type": "string"
			},
			{
				"internalType": "string",
				"name": "tmp_Company_Name",
				"type": "string"
			}
		],
		"name": "Ask_Be_Company",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			}
		],
		"name": "Buy",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "address",
				"name": "tmp_Address",
				"type": "address"
			}
		],
		"name": "Disallow_Asking",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			},
			{
				"internalType": "string",
				"name": "Product",
				"type": "string"
			},
			{
				"internalType": "string",
				"name": "Method",
				"type": "string"
			},
			{
				"internalType": "uint256",
				"name": "Expiration_Date",
				"type": "uint256"
			}
		],
		"name": "Processor_Work",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "Show_All_Asking_Data",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [],
		"stateMutability": "nonpayable",
		"type": "constructor"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "bytes32[]",
				"name": "Ids",
				"type": "bytes32[]"
			}
		],
		"name": "Show_All_Commidity_Id",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "bytes32[]",
				"name": "Ids",
				"type": "bytes32[]"
			}
		],
		"name": "Show_All_Processed_Id",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "bytes32[]",
				"name": "Ids",
				"type": "bytes32[]"
			}
		],
		"name": "Show_All_Supplied_Id",
		"type": "event"
	},
	{
		"inputs": [],
		"name": "Show_All_User_Data",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "address",
				"name": "Address",
				"type": "address"
			},
			{
				"indexed": false,
				"internalType": "string",
				"name": "Status",
				"type": "string"
			},
			{
				"indexed": false,
				"internalType": "string",
				"name": "Company_Address",
				"type": "string"
			},
			{
				"indexed": false,
				"internalType": "string",
				"name": "Company_Name",
				"type": "string"
			}
		],
		"name": "Show_Asking_Data",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			},
			{
				"components": [
					{
						"internalType": "bytes32",
						"name": "Id",
						"type": "bytes32"
					},
					{
						"internalType": "address",
						"name": "Owner",
						"type": "address"
					},
					{
						"internalType": "enum Good_Resume.State",
						"name": "Where",
						"type": "uint8"
					},
					{
						"internalType": "string",
						"name": "Ingredient",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Address",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Supply_Time",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Product",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Expiration_Date",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Good_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Proposed_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Customer_Service",
						"type": "uint256"
					},
					{
						"internalType": "uint256",
						"name": "Price",
						"type": "uint256"
					}
				],
				"indexed": false,
				"internalType": "struct Good_Resume.Good",
				"name": "tmp_Good",
				"type": "tuple"
			}
		],
		"name": "Show_Processed_Data",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			},
			{
				"components": [
					{
						"internalType": "bytes32",
						"name": "Id",
						"type": "bytes32"
					},
					{
						"internalType": "address",
						"name": "Owner",
						"type": "address"
					},
					{
						"internalType": "enum Good_Resume.State",
						"name": "Where",
						"type": "uint8"
					},
					{
						"internalType": "string",
						"name": "Ingredient",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Address",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Supply_Time",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Product",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Expiration_Date",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Good_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Proposed_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Customer_Service",
						"type": "uint256"
					},
					{
						"internalType": "uint256",
						"name": "Price",
						"type": "uint256"
					}
				],
				"indexed": false,
				"internalType": "struct Good_Resume.Good",
				"name": "tmp_Good",
				"type": "tuple"
			}
		],
		"name": "Show_Resume",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			},
			{
				"components": [
					{
						"internalType": "bytes32",
						"name": "Id",
						"type": "bytes32"
					},
					{
						"internalType": "address",
						"name": "Owner",
						"type": "address"
					},
					{
						"internalType": "enum Good_Resume.State",
						"name": "Where",
						"type": "uint8"
					},
					{
						"internalType": "string",
						"name": "Ingredient",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Address",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Supply_Time",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Product",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Expiration_Date",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Good_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Proposed_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Customer_Service",
						"type": "uint256"
					},
					{
						"internalType": "uint256",
						"name": "Price",
						"type": "uint256"
					}
				],
				"indexed": false,
				"internalType": "struct Good_Resume.Good",
				"name": "tmp_Good",
				"type": "tuple"
			}
		],
		"name": "Show_Supplied_Data",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": false,
				"internalType": "address",
				"name": "Address",
				"type": "address"
			},
			{
				"indexed": false,
				"internalType": "string",
				"name": "Name",
				"type": "string"
			},
			{
				"indexed": false,
				"internalType": "string",
				"name": "Password",
				"type": "string"
			},
			{
				"indexed": false,
				"internalType": "string",
				"name": "Status",
				"type": "string"
			},
			{
				"indexed": false,
				"internalType": "bool",
				"name": "Enable_Ask",
				"type": "bool"
			}
		],
		"name": "Show_User_Data",
		"type": "event"
	},
	{
		"inputs": [
			{
				"internalType": "string",
				"name": "Ingredient",
				"type": "string"
			}
		],
		"name": "Supplier_Work",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "string",
				"name": "tmp_Name",
				"type": "string"
			},
			{
				"internalType": "string",
				"name": "tmp_Password",
				"type": "string"
			}
		],
		"name": "User_Join",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "List_All_Commidity_Id",
		"outputs": [
			{
				"internalType": "bytes32[]",
				"name": "",
				"type": "bytes32[]"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "List_All_Processed_Id",
		"outputs": [
			{
				"internalType": "bytes32[]",
				"name": "",
				"type": "bytes32[]"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "List_All_Supplied_Id",
		"outputs": [
			{
				"internalType": "bytes32[]",
				"name": "",
				"type": "bytes32[]"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			}
		],
		"name": "List_Commidity_Data",
		"outputs": [
			{
				"components": [
					{
						"internalType": "bytes32",
						"name": "Id",
						"type": "bytes32"
					},
					{
						"internalType": "address",
						"name": "Owner",
						"type": "address"
					},
					{
						"internalType": "enum Good_Resume.State",
						"name": "Where",
						"type": "uint8"
					},
					{
						"internalType": "string",
						"name": "Ingredient",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Address",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Supply_Time",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Product",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Expiration_Date",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Good_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Proposed_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Customer_Service",
						"type": "uint256"
					},
					{
						"internalType": "uint256",
						"name": "Price",
						"type": "uint256"
					}
				],
				"internalType": "struct Good_Resume.Good",
				"name": "",
				"type": "tuple"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			}
		],
		"name": "List_Processed_Data",
		"outputs": [
			{
				"components": [
					{
						"internalType": "bytes32",
						"name": "Id",
						"type": "bytes32"
					},
					{
						"internalType": "address",
						"name": "Owner",
						"type": "address"
					},
					{
						"internalType": "enum Good_Resume.State",
						"name": "Where",
						"type": "uint8"
					},
					{
						"internalType": "string",
						"name": "Ingredient",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Address",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Supply_Time",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Product",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Expiration_Date",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Good_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Proposed_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Customer_Service",
						"type": "uint256"
					},
					{
						"internalType": "uint256",
						"name": "Price",
						"type": "uint256"
					}
				],
				"internalType": "struct Good_Resume.Good",
				"name": "",
				"type": "tuple"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "bytes32",
				"name": "Id",
				"type": "bytes32"
			}
		],
		"name": "List_Supplied_Data",
		"outputs": [
			{
				"components": [
					{
						"internalType": "bytes32",
						"name": "Id",
						"type": "bytes32"
					},
					{
						"internalType": "address",
						"name": "Owner",
						"type": "address"
					},
					{
						"internalType": "enum Good_Resume.State",
						"name": "Where",
						"type": "uint8"
					},
					{
						"internalType": "string",
						"name": "Ingredient",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Supply_Address",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Supply_Time",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Product",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Process_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Expiration_Date",
						"type": "uint256"
					},
					{
						"internalType": "string",
						"name": "Good_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Name",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Agent_Address",
						"type": "string"
					},
					{
						"internalType": "string",
						"name": "Proposed_Method",
						"type": "string"
					},
					{
						"internalType": "uint256",
						"name": "Customer_Service",
						"type": "uint256"
					},
					{
						"internalType": "uint256",
						"name": "Price",
						"type": "uint256"
					}
				],
				"internalType": "struct Good_Resume.Good",
				"name": "",
				"type": "tuple"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "Show_Personal_Data",
		"outputs": [
			{
				"internalType": "string",
				"name": "",
				"type": "string"
			},
			{
				"internalType": "string",
				"name": "",
				"type": "string"
			}
		],
		"stateMutability": "view",
		"type": "function"
	}
];

var ResumeContract = new web3.eth.Contract(abi, address, {
    from: web3.eth.defaultAccount
}); 

ResumeContract.methods.Show_Personal_Data().call(function(error, result)
{
    if(!error)
        {
            $("#name").html(result[0]);
            $("#now_identity").html(result[1]);
        }
    else
        console.error(error);
});



//將合約傳來的資料放進data//


function list_supplied(){
	return new Promise((resolve,reject)=>{
		ResumeContract.methods.List_All_Supplied_Id().call(function(error, result)
		{
			if(!error)
			{
				console.log(result);
				Supplied_Id = result;
				resolve();
			}
			else
			{
				console.error(error);
				reject();
			}
		});
	});
}

function list_data(num){
	return new Promise((resolve,reject)=>{
		ResumeContract.methods.List_Supplied_Data(Supplied_Id[num]).call(function(error, supplied)
		{
			if(!error) 
			{
				console.log(supplied);
				if(supplied.Id != '0x0000000000000000000000000000000000000000000000000000000000000000')
					data.push({
						dataid : supplied.Id,
						ingredient : supplied.Ingredient,
						supply_name : supplied.Supply_Name,
						supply_address : supplied.Supply_Address,
						supply_time : supplied.Supply_Time
					});
				console.log(data);
				resolve();
			}
			else
				console.error(error);
		}); 
	});
}

var data = [];

var Supplied_Id;

async function Start(){
	console.log("start");
	await list_supplied();
	for(var count = 0; count < Supplied_Id.length; count++) await list_data(count);
	build_box();
	console.log("done");
}


function build_box(){
	var size=data.length;
	var tbody=document.querySelector('#main');
	var tmp = Math.floor(size/8);
	console.log("tmp : " + tmp);
	for(var i = 0 ; i < Math.ceil(size/8) ; i++){//創建'box'
		console.log("i : " + i);
		var tr = document.createElement('tr');
		tr.style.cssText=';margin-left: 64px; text-align:center;  overflow: scroll';
		tr.id='row'+(i+1);
		tbody.appendChild(tr);
		if(i<tmp){
			for(var j=0 ; j<8 ; j++){
				var td = document.createElement('td');
				td.id='box'+(i*8+j+1);
				td.className = 'box';
				tr.appendChild(td);   
			}
		}
		else{
			for(var j=0 ; j<size-tmp*8 ; j++){
				var td = document.createElement('td');
				td.id='box'+(tmp*8+j+1);
				td.className = 'box';
				tr.appendChild(td);
			}
		}
	}

	console.log("data length : "+data.length);
	for(var i=0;i<data.length;i++){
		var table = document.createElement('table');//每個box內部再變成一個table
		var box = document.querySelector('#box'+(i+1));
		table.width = '148px';
		table.id='box_table'+(i+1);
		table.style.cssText = 'text-align: center;vertical-align: middle !important;height: 100px;';
		box.appendChild(table);

		var tr = document.createElement('tr');//box內部table的第一row
		tr.style.cssText='text-align:center;height:65px;';
		table = document.querySelector('#box_table'+(i+1));
		table.appendChild(tr);

		var td = document.createElement('td');//box內部table的第一row的第一col(放產品名字)
		td.class='font_roboto';
		td.style.cssText='text-align:center';
		td.colSpan='2';
		console.log("data:" + data[i].ingredient);
		td.innerHTML=data[i].ingredient;
		tr.appendChild(td);

		tr = document.createElement('tr');//box內部table的第二row(裡面有兩個td)
		table.appendChild(tr);

		td = document.createElement('td');////box內部table的第二row的第一col(td)(放加工按鈕)
		td.width='74px';
		tr.appendChild(td);
		//下面是加上生產按鈕及跳出小框框//
		td.innerHTML=td.innerHTML+`
		<button type="button" data-bs-toggle="modal" data-bs-target="#process${i+1}" class="produce_btn" >加工</button>
		<div class="modal fade" id="process${i+1}">
			<div class="modal-dialog">
				<div class="modal-content">
					<div class="modal-header">
						<h4>加工</h4>
						<button type="button" class="close" data-bs-dismiss="modal" aria-hidden="true">&times;</button>
					</div>
					<div class="modal-body">
						<form>
							<div class="form-group">
								<input type="text" class="form-control ingredient" style="margin-top:13px" placeholder="輸入產品名稱" id="name${i}"/>
								<input type="text" class="form-control ingredient" style="margin-top:13px" placeholder="輸入加工方法" id="method${i}"/>
								<input type="text" class="form-control ingredient" style="margin-top:13px"   placeholder="輸入有效期限" id="expirationdate${i}"/>
								<p class="form-control" style="margin-top:13px; text-align: left;">成分: ${data[i].ingredient}</p>
								<p class="form-control" style="margin-top:13px; text-align: left;">製造日期 : ${data[i].supply_time}</p>
								<p class="form-control" style="text-align: left;">製造商地址 : ${data[i].supply_address}</p>
								<p class="form-control" style="text-align: left;">製造商名字 : ${data[i].supply_name}</p>
								<p class="form-control" style="margin-top:13px; text-align: left;">成分: ${data[i].ingredient}</p>
								<p class="form-control" style="margin-top:13px; text-align: left;">加工廠名字 : ${data[i].process_name}</p>
								<p class="form-control" style="text-align: left;">加工廠地址 : ${data[i].process_address}</p>
							</div>
						</form>
					</div>
					<div class="modal-footer">
						<button type="button" id=${i} class="btn btn-info" onclick="handle_click(this)" data-bs-dismiss="modal">加工</button>
						<button type="button" class="btn btn-info" data-bs-dismiss="modal">取消</button>
					</div>
				</div>
			</div> 
		</div>
		`;
	}
}

Start();

function handle_click(element){
    console.log("按了第"+element.id+"個產品");
    ResumeContract.methods.Processor_Work(data[element.id].dataid, $("#name"+element.id).val(), $("#method"+element.id).val(), $("#expirationdate"+element.id).val()).estimateGas({from : web3.eth.defaultAccount}, function(error, result){
        if(!error){
            console.log(result);
            ResumeContract.methods.Processor_Work(data[element.id].dataid, $("#name"+element.id).val(), $("#method"+element.id).val(), $("#expirationdate"+element.id).val()).send({from : web3.eth.defaultAccount, gas: result}, function(error2, result2){
                if(!error2) console.log(result2);
                else console.log(error2);
            });
        }
        else console.log(error);
    });
    console.log("新增產品成功");
}