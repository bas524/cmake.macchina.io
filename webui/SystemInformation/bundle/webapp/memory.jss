if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var memory = {
    stats: system.exec(system.osName == "Darwin" ? "memory_pressure" : (system.osName == "Linux" ? "free" : "wmic OS get FreePhysicalMemory,FreeVirtualMemory,FreeSpaceInPagingFiles /VALUE"))
};

response.contentType = 'application/json';
response.write(JSON.stringify(memory));
response.send();
