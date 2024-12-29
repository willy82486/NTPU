pragma solidity = 0.8.7;

// 商品 Good
// 履歷 Resume
// 原物料商 Supplier
// 加工商 Processor
// 代理商 Agent (Packer??)
// 消費者 Customer
// 我們(發行人) Government


//delete 篩選 0
contract DateTime {
        /*
         *  Date and Time utilities for ethereum contracts
         *
         */
        struct _DateTime {
                uint16 year;
                uint8 month;
                uint8 day;
                uint8 hour;
                uint8 minute;
                uint8 second;
                uint8 weekday;
        }

        uint constant DAY_IN_SECONDS = 86400;
        uint constant YEAR_IN_SECONDS = 31536000;
        uint constant LEAP_YEAR_IN_SECONDS = 31622400;

        uint constant HOUR_IN_SECONDS = 3600;
        uint constant MINUTE_IN_SECONDS = 60;

        uint16 constant ORIGIN_YEAR = 1970;

        function isLeapYear(uint16 year) public pure returns (bool) {
                if (year % 4 != 0) {
                        return false;
                }
                if (year % 100 != 0) {
                        return true;
                }
                if (year % 400 != 0) {
                        return false;
                }
                return true;
        }

        function leapYearsBefore(uint year) public pure returns (uint) {
                year -= 1;
                return year / 4 - year / 100 + year / 400;
        }

        function getDaysInMonth(uint8 month, uint16 year) public pure returns (uint8) {
                if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                        return 31;
                }
                else if (month == 4 || month == 6 || month == 9 || month == 11) {
                        return 30;
                }
                else if (isLeapYear(year)) {
                        return 29;
                }
                else {
                        return 28;
                }
        }

        function parseTimestamp(uint timestamp) public pure returns (_DateTime memory dt) {
                uint secondsAccountedFor = 0;
                uint buf;
                uint8 i;

                // Year
                dt.year = getYear(timestamp);
                buf = leapYearsBefore(dt.year) - leapYearsBefore(ORIGIN_YEAR);

                secondsAccountedFor += LEAP_YEAR_IN_SECONDS * buf;
                secondsAccountedFor += YEAR_IN_SECONDS * (dt.year - ORIGIN_YEAR - buf);

                // Month
                uint secondsInMonth;
                for (i = 1; i <= 12; i++) {
                        secondsInMonth = DAY_IN_SECONDS * getDaysInMonth(i, dt.year);
                        if (secondsInMonth + secondsAccountedFor > timestamp) {
                                dt.month = i;
                                break;
                        }
                        secondsAccountedFor += secondsInMonth;
                }

                // Day
                for (i = 1; i <= getDaysInMonth(dt.month, dt.year); i++) {
                        if (DAY_IN_SECONDS + secondsAccountedFor > timestamp) {
                                dt.day = i;
                                break;
                        }
                        secondsAccountedFor += DAY_IN_SECONDS;
                }

                // Hour
                dt.hour = getHour(timestamp);

                // Minute
                dt.minute = getMinute(timestamp);

                // Second
                dt.second = getSecond(timestamp);

                // Day of week.
                dt.weekday = getWeekday(timestamp);
        }

        function getYear(uint timestamp) public pure returns (uint16) {
                uint secondsAccountedFor = 0;
                uint16 year;
                uint numLeapYears;

                // Year
                year = uint16(ORIGIN_YEAR + timestamp / YEAR_IN_SECONDS);
                numLeapYears = leapYearsBefore(year) - leapYearsBefore(ORIGIN_YEAR);

                secondsAccountedFor += LEAP_YEAR_IN_SECONDS * numLeapYears;
                secondsAccountedFor += YEAR_IN_SECONDS * (year - ORIGIN_YEAR - numLeapYears);

                while (secondsAccountedFor > timestamp) {
                        if (isLeapYear(uint16(year - 1))) {
                                secondsAccountedFor -= LEAP_YEAR_IN_SECONDS;
                        }
                        else {
                                secondsAccountedFor -= YEAR_IN_SECONDS;
                        }
                        year -= 1;
                }
                return year;
        }

        function getMonth(uint timestamp) public pure returns (uint8) {
                return parseTimestamp(timestamp).month;
        }

        function getDay(uint timestamp) public pure returns (uint8) {
                return parseTimestamp(timestamp).day;
        }

        function getHour(uint timestamp) public pure returns (uint8) {
                return uint8((timestamp / 60 / 60) % 24);
        }

        function getMinute(uint timestamp) public pure returns (uint8) {
                return uint8((timestamp / 60) % 60);
        }

        function getSecond(uint timestamp) public pure returns (uint8) {
                return uint8(timestamp % 60);
        }

        function getWeekday(uint timestamp) public pure returns (uint8) {
                return uint8((timestamp / DAY_IN_SECONDS + 4) % 7);
        }

        function toTimestamp(uint16 year, uint8 month, uint8 day) public pure returns (uint timestamp) {
                return toTimestamp(year, month, day, 0, 0, 0);
        }

        function toTimestamp(uint16 year, uint8 month, uint8 day, uint8 hour) public pure returns (uint timestamp) {
                return toTimestamp(year, month, day, hour, 0, 0);
        }

        function toTimestamp(uint16 year, uint8 month, uint8 day, uint8 hour, uint8 minute) public pure returns (uint timestamp) {
                return toTimestamp(year, month, day, hour, minute, 0);
        }

        function toTimestamp(uint16 year, uint8 month, uint8 day, uint8 hour, uint8 minute, uint8 second) public pure returns (uint timestamp) {
                uint16 i;

                // Year
                for (i = ORIGIN_YEAR; i < year; i++) {
                        if (isLeapYear(i)) {
                                timestamp += LEAP_YEAR_IN_SECONDS;
                        }
                        else {
                                timestamp += YEAR_IN_SECONDS;
                        }
                }

                // Month
                uint8[12] memory monthDayCounts;
                monthDayCounts[0] = 31;
                if (isLeapYear(year)) {
                        monthDayCounts[1] = 29;
                }
                else {
                        monthDayCounts[1] = 28;
                }
                monthDayCounts[2] = 31;
                monthDayCounts[3] = 30;
                monthDayCounts[4] = 31;
                monthDayCounts[5] = 30;
                monthDayCounts[6] = 31;
                monthDayCounts[7] = 31;
                monthDayCounts[8] = 30;
                monthDayCounts[9] = 31;
                monthDayCounts[10] = 30;
                monthDayCounts[11] = 31;

                for (i = 1; i < month; i++) {
                        timestamp += DAY_IN_SECONDS * monthDayCounts[i - 1];
                }

                // Day
                timestamp += DAY_IN_SECONDS * (day - 1);

                // Hour
                timestamp += HOUR_IN_SECONDS * (hour);

                // Minute
                timestamp += MINUTE_IN_SECONDS * (minute);

                // Second
                timestamp += second;

                return timestamp;
        }
}

contract Good_Resume
{
    // Tools
    DateTime datetime;
    function String_To_Byte32(string memory tmp_String) internal pure returns(bytes32 Output)
    {
        assembly
        {
            Output := mload(add(tmp_String,32))
        }
    }

    function Byte32_To_String(bytes32 _bytes32) internal pure returns (string memory) {
        uint8 i = 0;
        while(i < 32 && _bytes32[i] != 0) {
            i++;
        }
        bytes memory bytesArray = new bytes(i);
        for (i = 0; i < 32 && _bytes32[i] != 0; i++) {
            bytesArray[i] = _bytes32[i];
        }
        return string(bytesArray);
    }

    function append(string memory a, string memory b) internal pure returns (string memory) 
    {
        return string(abi.encodePacked(a, b));
    }
    // Structure
    constructor()
    {
        Government = msg.sender;
    }

    address Government;
    mapping(address => User) All_User_Data;
    address[] All_User_Address;
    address[] Suppliers_Address;
    address[] Processors_Address;
    address[] Agents_Address;
    address[] Asking_Adress;
    mapping(address => Identify) Asking_Data; 
    string[] Company_str = ["Customer", "Supplier", "Processor", "Agent"];

    mapping(bytes32 => Good) All_Good_Data;
    bytes32[] All_Good;
    mapping(address => bytes32[]) Customer_Owned; //0613 該消費者(Addr)擁有的商品(bytes32)

    struct User
    {
        //address User_Address;
        string User_Name;
        string User_Password;
        Identify Who;
        bool Enable_Ask;
    }

    struct Identify
    {
        Company Status;
        string Company_Address; 
        string Company_Name; 
        //?
    }

    enum Company
    {
        Customer, //0
        Supplier, //1
        Processor, //2
        Agent //3
    }
    
    struct Good
    {
        bytes32 Id;
        address Owner;
        State Where;
        
        string Ingredient;
        string Supply_Name;
        string Supply_Address; 
        uint Supply_Time; 
        
        string Product;
        string Process_Name;
        string Process_Address;
        string Process_Method;
        uint Expiration_Date;
        
        string Good_Name;
        string Agent_Name;
        string Agent_Address;
        string Proposed_Method; 
        uint256 Customer_Service; 
        uint256 Price;
    }

    enum State
    {
        Supplied,
        Processed,
        Commidity
    }

    bytes32[] Supplied_Id;
    bytes32[] Processed_Id;
    bytes32[] Commidity_Id;
    

    // Modifier
    modifier Only_Government()
    {
        require(msg.sender == Government,"not government.");
        _;
    }
    
    modifier Only_Nobody()
    {
        require(All_User_Data[msg.sender].Who.Status == Company.Customer,"already company.");
        _;
    }
    
    modifier Not_Join()
    {
        require(Check_Join(msg.sender) == false,"already join.");
        _;
    }

    modifier Join()
    {
        require(Check_Join(msg.sender) == true,"not join.");
        _;
    }

    modifier Only_Supplier()
    {
        require(All_User_Data[msg.sender].Who.Status == Company.Supplier);
        _;
    }

    modifier Only_Processor()
    {
        require(All_User_Data[msg.sender].Who.Status == Company.Processor);
        _;
    }

    modifier Only_Agent()
    {
        require(All_User_Data[msg.sender].Who.Status == Company.Agent);
        _;
    }
    // Function
    function Check_Join(address tmp_Address) internal view returns(bool) //檢查已經加入
    {
        for(uint i=0;i<All_User_Address.length;i++)
        {
            if(All_User_Address[i] == tmp_Address) return true;
        }
        return false;
    } 

    function User_Join(string memory tmp_Name, string memory tmp_Password) public Not_Join //加入
    {
        // initial User Data
        All_User_Data[msg.sender] = User(tmp_Name, 
                                        tmp_Password,
                                        Identify(Company.Customer, "", ""),
                                        true);
        /*
        All_User_Data[msg.sender].User_Name = String_To_Byte32(tmp_Name);
        All_User_Data[msg.sender].User_Password = String_To_Byte32(tmp_Password);
        All_User_Data[msg.sender].Who.Status = Company.Customer;
        All_User_Data[msg.sender].Who.Company_Address = "";
        All_User_Data[msg.sender].Who.Company_Name = "";
        */
        All_User_Address.push(msg.sender);
    }

    function Show_All_User_Data() public Only_Government //政府看所有人
    {
        for(uint i=0;i<All_User_Address.length;i++)
        {
            address tmp_Address = All_User_Address[i];
            emit Show_User_Data(tmp_Address, 
                                All_User_Data[tmp_Address].User_Name,
                                All_User_Data[tmp_Address].User_Password, 
                                Company_str[uint(All_User_Data[tmp_Address].Who.Status)],
                                All_User_Data[tmp_Address].Enable_Ask);
        }
    }

    function Show_Personal_Data() public view returns (string memory, string memory)
    {
        return(All_User_Data[msg.sender].User_Name, Company_str[uint(All_User_Data[msg.sender].Who.Status)]);
    }

    function Ask_Be_Company(Company tmp_Choose, string memory tmp_Company_Address, string memory tmp_Company_Name) 
    public Only_Nobody //申請成為公司(限未成為且未申請)
    {
        Asking_Adress.push(msg.sender);
        All_User_Data[msg.sender].Enable_Ask = false;

        Asking_Data[msg.sender] = Identify(tmp_Choose, 
                                            tmp_Company_Address, 
                                            tmp_Company_Name);
        /*
        Asking_Data[msg.sender].Status = tmp_Choose;
        Asking_Data[msg.sender].Company_Address = String_To_Byte32(tmp_Company_Address);
        Asking_Data[msg.sender].Company_Name = String_To_Byte32(tmp_Company_Name);
        */
    }
    
    function Show_All_Asking_Data() public Only_Government //政府看所有申請
    {
        for(uint i=0;i<Asking_Adress.length;i++)
        {
            address tmp_Address = Asking_Adress[i];
            emit Show_Asking_Data(tmp_Address, 
                                    Company_str[uint(Asking_Data[tmp_Address].Status)], 
                                    Asking_Data[tmp_Address].Company_Address,
                                    Asking_Data[tmp_Address].Company_Name);
        }
    }

    function Remove_From_Asking(address tmp_Address) internal // 從Asking list 移除
    {
        for(uint i=0;i<Asking_Adress.length;i++)
        {
            if(Asking_Adress[i] == tmp_Address)
            {
                delete Asking_Adress[i];
                break;
            }
        }
        delete Asking_Data[tmp_Address];
    }

    function Allow_Asking(address tmp_Address) public Only_Government // 政府同意申請
    {
        All_User_Data[tmp_Address].Who = Asking_Data[tmp_Address];
        Remove_From_Asking(tmp_Address);
        uint Do = uint(All_User_Data[tmp_Address].Who.Status);
        if(Do == 1) Suppliers_Address.push(tmp_Address);
        else if(Do == 2) Processors_Address.push(tmp_Address);
        else if(Do == 3) Agents_Address.push(tmp_Address);
    }

    function Disallow_Asking(address tmp_Address) public Only_Government // 政府不同意申請
    {
        Remove_From_Asking(tmp_Address);
        All_User_Data[tmp_Address].Enable_Ask = true;
    }

    function Supplier_Work(string memory Ingredient) public Only_Supplier // 原物料 創造產品
    {
        uint T = block.timestamp;
        bytes32 Id = String_To_Byte32(append(string(Ingredient), Byte32_To_String(bytes32(T))));
        All_Good_Data[Id] = Good(Id, msg.sender, State.Supplied, Ingredient,
                            All_User_Data[msg.sender].Who.Company_Name,
                            All_User_Data[msg.sender].Who.Company_Address,
                            T, "", "", "","",0,"","","","",0,0); //not use yet
        Supplied_Id.push(Id);
    }

    function List_All_Supplied_Id() public view Only_Processor returns(bytes32[] memory)
    {
        //emit Show_All_Supplied_Id(Supplied_Id);
        return(Supplied_Id);
    }

    function List_Supplied_Data(bytes32 Id) public view Only_Processor returns(Good memory)
    {
        //emit Show_Supplied_Data(Id, All_Good_Data[Id]); // 改成需要看的就好
        return(All_Good_Data[Id]);
    }

    function Processor_Work(bytes32 Id, string memory Product, string memory Method, uint Expiration_Date) public Only_Processor
    {
        All_Good_Data[Id].Owner = msg.sender;
        All_Good_Data[Id].Product = Product;
        All_Good_Data[Id].Process_Name = All_User_Data[msg.sender].Who.Company_Name;
        All_Good_Data[Id].Process_Address = All_User_Data[msg.sender].Who.Company_Address;
        All_Good_Data[Id].Process_Method = Method;
        All_Good_Data[Id].Expiration_Date = Expiration_Date;

        Remove_From_Supplied(Id);

        Processed_Id.push(Id);
    }

    function Remove_From_Supplied(bytes32 Id) internal
    {
        for(uint i=0;i<Supplied_Id.length;i++)
        {
            if(Id == Supplied_Id[i])
            {
                delete Supplied_Id[i];
                break;
            }
        }
    }

    function List_All_Processed_Id() public view Only_Agent returns(bytes32[] memory)
    {
        //emit Show_All_Processed_Id(Processed_Id);
        return(Processed_Id);
    }

    function List_Processed_Data(bytes32 Id) public view Only_Agent returns(Good memory)
    {
        //emit Show_Processed_Data(Id, All_Good_Data[Id]);
        return(All_Good_Data[Id]);
    }

    function Agent_Work(bytes32 Id, string memory Good_Name, string memory Proposed_Method, uint Customer_Service, uint Price)
    public Only_Agent
    {
        All_Good_Data[Id].Owner = msg.sender;
        All_Good_Data[Id].Where = State.Commidity;
        All_Good_Data[Id].Good_Name = Good_Name;
        All_Good_Data[Id].Agent_Name = All_User_Data[msg.sender].Who.Company_Name;
        All_Good_Data[Id].Agent_Address = All_User_Data[msg.sender].Who.Company_Address;
        All_Good_Data[Id].Proposed_Method = Proposed_Method;
        All_Good_Data[Id].Customer_Service = Customer_Service;
        All_Good_Data[Id].Price = Price;

        Remove_From_Processed(Id);

        Commidity_Id.push(Id);
    }

    function Remove_From_Processed(bytes32 Id) internal
    {
        for(uint i=0;i<Processed_Id.length;i++)
        {
            if(Processed_Id[i] == Id)
            {
                delete Processed_Id[i];
                break;
            }
        }
    }

    function List_All_Commidity_Id() public view Only_Nobody returns(bytes32[] memory)
    {
        //emit Show_All_Commidity_Id(Commidity_Id);
        return(Commidity_Id);
    }

    function Buy(bytes32 Id) public Only_Nobody
    {
        //0613
        All_Good_Data[Id].Owner = msg.sender; //擁有者為消費者
        Remove_From_Commidity(Id); //從公開商品欄移除
        Customer_Owned[msg.sender].push(Id); //加入該消費者商品中
        //0613
        emit Show_Resume(Id, All_Good_Data[Id]);
    }

    function List_Commidity_Data(bytes32 Id) public view Only_Nobody returns(Good memory)
    {
        //emit Show_Processed_Data(Id, All_Good_Data[Id]);
        return(All_Good_Data[Id]);
    }
    
    //0613
    function Remove_From_Commidity(bytes32 Id) internal
    {
        for(uint i=0;i<Commidity_Id.length;i++)
        {
            if(Id == Commidity_Id[i])
            {
                delete Commidity_Id[i];
                break;
            }
        }
    }


    //0613

    // Event  //顯示用
    event Show_User_Data(address Address, string Name, string Password, string Status, bool Enable_Ask);
    event Show_Asking_Data(address Address, string Status, string Company_Address, string Company_Name);
    event Show_All_Supplied_Id(bytes32[] Ids);
    event Show_Supplied_Data(bytes32 Id, Good tmp_Good);
    event Show_All_Processed_Id(bytes32[] Ids);
    event Show_Processed_Data(bytes32 Id, Good tmp_Good);
    event Show_All_Commidity_Id(bytes32[] Ids);
    event Show_Resume(bytes32 Id, Good tmp_Good);
}


/*
bytes32 Id;
address Owner;
State Where;
//上
string Ingredient; //生乳
string Supply_Name;
string Supply_Address; 
uint Supply_Time; 
//中
string Product;
string Process_Name;
string Process_Address;
string Process_Method;
uint Expiration_Date;
//下
string Good_Name;
string Agent_Name;
string Agent_Address;
string Proposed_Method; 
uint256 Customer_Service; 
uint256 Price;
*/