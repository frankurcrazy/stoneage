function data()
	grouplist = {{1, 2, 0, "測試綫路"}
							}

	serlist = {
						{"192.168.1.2","19065","電信綫路"},
						{"192.168.1.2","19065","網通綫路"},
				}
end

function main()
	data()
	ServerList.SetGroupMaxNum(table.getn(grouplist))
	for i = 1, table.getn(grouplist) do
		ServerList.SetGroupList(i - 1, grouplist[i][1], grouplist[i][2], grouplist[i][3], grouplist[i][4])
	end
	for i = 1, table.getn(serlist) do
		ServerList.SetServerList(i - 1, serlist[i][1], serlist[i][2], serlist[i][3])
	end
end

