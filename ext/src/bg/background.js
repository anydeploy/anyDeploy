// if you checked "fancy-settings" in extensionizr.com, uncomment this lines

//var settings = new Store("settings", {
  //   "sample_setting": "This is how you use Store.js to remember values"
 //});
var tablink;
var repo;

var re = new RegExp("https://github.com/(.*)/(.*)")



var github = new Github({
  token: "dc91aa9f9b18fdbb76f98aaca0ae83b6c8600421",
  auth: "oauth"
});




chrome.pageAction.onClicked.addListener(function(tab) {
	var splitLink = tablink.split("https://github.com")[1];
	var username = splitLink.split("/")[1];
	var repoName = splitLink.split("/")[2];
	var travisBuildLink = "https://travis-ci.org/Jack-Collins/" + repoName;
	repo = github.getRepo(username, repoName);
	try{
		//repo.fork(function(err) {console.log(err)});
		//repo.deleteRepo(function(err, res){console.log(res)})
		console.log("I can do what I like with the repo here of values: " + username +  "/" + repoName);
		console.log("travisBuildLink: " + travisBuildLink);

	}
	catch(err1){
		
		}
	chrome.tabs.create({
		'url' : 'https://travis-ci.org',
		'selected' : true
	}, function(tab) {
	});
});

 function checkForValidUrl(tabId, changeInfo, tab) {
	if (re.test(tab.url)) {
		chrome.pageAction.show(tabId);
		tablink = tab.url;	
	}
};

 // Checks for URL change
chrome.tabs.onUpdated.addListener(checkForValidUrl);

//example of using a message handler from the inject scripts
chrome.extension.onMessage.addListener(
  function(request, sender, sendResponse) {
  	chrome.pageAction.show(sender.tab.id);
    sendResponse();
  });
