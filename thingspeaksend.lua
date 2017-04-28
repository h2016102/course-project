 	--Connect to wifi where ssid and password are hardcoded
 	wifi.sta.config("shivi" ,"shivi1893")
 	wifi.sta.connect()
 
 	--Create a function sendThingSpeak which establishes connection and sends data online
 	function sendThingSpeak(level)
 		local connout = nil
 		
 		--Create TCP connection
		connout = net.createConnection(net.TCP, 0)
		
	--Receive details from online server/website about status etc
		connout:on("receive", function(connout, payloadout)
			if (string.find(payloadout, "Status: 200 OK") ~= nil) then
				print("Posted OK");
			end
		end)
		
		--Connection is On 
		connout:on("connection", function(connout, payloadout)
	 
			print ("Posting...")
			
			--Data is being posted on thingspeak channel 
			connout:send("GET http://52.7.7.190/update?api_key=Q00XI7ZOGTMJBN55&field1=6\r\n\r\n")
			print("Data Sent")
		end)
	 
		connout:on("disconnection", function(connout, payloadout)
			connout:close()
			collectgarbage()
		end)
		
		--A socket is created which binds port number to IP address of the website. This creates a medium/channel for transfer of data
		connout:connect(80,'52.7.7.190')
	end
	--A timer which sends data at a frequency of 1 minute
	tmr.alarm(1, 60000, 1, function() sendThingSpeak(0) end)