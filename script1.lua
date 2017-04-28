wifi.sta.config("shivi" ,"shivi1893")
wifi.sta.connect()
 
 	function GetDataFromThingspeak(_server, _port, _channel, _field)
 	--print("Querying data from thingspeak")
 	conn=net.createConnection(net.TCP, 0) 
 	conn:on("receive", function(conn, payload)
 	   tmr.wdclr() 
 	   --print(payload) 
	   tmr.wdclr()
	   conn:close() 
	   ThingspeakReply = payload
	   print("Query ".._server..":".._port.." channel".._channel.." field".._field.." REPLY: "..ThingspeakReply.."\n")
	   
	end)
	conn:connect(_port,_server)
	--Send request for receiving data in payload 
	conn:send("GET /channels/263048/fields/1/last?key=ND74EYBDOR6TQBTD HTTP/1.1\r\n")
	conn:send('Host: 52.7.7.190\r\nAccept: */*\r\nUser-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n\r\n')
	conn:on("disconnection", function(conn)
			  --print("Got disconnection...")
			 conn=nil
  end)
	end
	-- END GET DATA FROM THINGSPEAK



	function data_init()
  if ThingspeakReply == nil then
		  GetDataFromThingspeak("52.7.7.190", 80, 263048, 1)
	   else
   print("Last entry in Thingspeak database: "..ThingspeakReply.."\n")
	   -- now a valid reply is available, do whatever you want with the read value
	   end
	   

	end

	tmr.alarm(0,5000, 1, function() data_init() end )