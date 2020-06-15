if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var processes = {
    list: system.exec(system.osName == "Darwin" ? "top -l 1" : (system.osName == "Linux" ? "top -b -n1" : "CHCP 65001 && tasklist"))
};

response.contentType = 'application/json';
response.write(JSON.stringify(processes));
response.send();
