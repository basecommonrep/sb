function setlang( lang, act, page, section, dbname, chapter, fname, from, sortby ) {
  var actstr;
  
  actstr = document.location.pathname;

  if ( actstr.lastIndexOf(".php") == -1 )
  	actstr = "search.php?";
  else 
	actstr = actstr.substr(actstr.lastIndexOf("/")+1, 1000)+"?";

  if ( act != "" )
  	actstr = actstr + "action="+act;

  if ( dbname != "" )
  	actstr = actstr + "&dbname="+dbname;

  if ( section != "" )
  	actstr = actstr + "&section="+section;
  	
  if ( page != "" )
  	actstr = actstr + "&page="+page;

  if ( lang != "" )
  	actstr = actstr + "&lang="+lang;

  if ( chapter != "" )
  	actstr = actstr + "&chapter="+chapter;

  if ( fname != "" )
  	actstr = actstr + "&fname="+fname;

  if ( from != "" )
  	actstr = actstr + "&from="+fname;

  if ( sortby != "" )
  	actstr = actstr + "&sortby="+sortby;

  document.location.href=actstr;
}

function doAction(act, dbname, section, page, fname) {
  var actstr;
  
  actstr = document.location.pathname;

  if ( actstr.lastIndexOf(".php") == -1 )
  	actstr = "search.php?";
  else 
	actstr = actstr.substr(actstr.lastIndexOf("/")+1, 1000)+"?";
  
  if ( act != "" )
  	actstr = actstr + "action="+act;

  if ( dbname != "" )
  	actstr = actstr + "&dbname="+dbname;

  if ( section != "" )
  	actstr = actstr + "&section="+section;
  	
  if ( page != "" )
  	actstr = actstr + "&page="+page;

  if ( fname != "" )
  	actstr = actstr + "&fname="+fname;
  
  document.all["Message"].style.visibility = "visible";
  document.all["MainTable"].style.visibility = "hidden";
  window.scrollTo(0,0);
  document.forms[0].action = actstr;
  document.forms[0].submit();
}

function ata( s ) {
  if (_active != null)
    with (_active) {
      focus();value += s;focus();
    }
}

function clf(fname) {
  with (document.forms[0].elements[fname]) {
    focus();
    value="";
 }
}

function clrall() {
  for (i = 0; i < searchbul.length; i++)
    if (searchbul.elements[i].type == "text")
      searchbul.elements[i].value="";
}

var _active = null, _accessed = "x";

function ma(edt,idx) {
  _active = edt;
  r = new RegExp("x"+idx+"x", "");
  if (_accessed.search(r) == -1) {
    _accessed += idx+"x";
  }
}

function _movelb() {
  with (document.all.LogicBar.style) {
    posTop = 150 + document.body.scrollTop;
    posRight = 30;
  }
}

function printpr() {
  var PROMPT = 1;
  var OLECMDID = 7;
  var WebBrowser = '<OBJECT ID="WebBrowser1" WIDTH=0 HEIGHT=0 CLASSID="CLSID:8856F961-340A-11D0-A96B-00C04FD705A2"></OBJECT>';
  document.body.insertAdjacentHTML('beforeEnd', WebBrowser);
  WebBrowser1.ExecWB(OLECMDID, PROMPT);
  WebBrowser1.outerHTML = "";
};

function addtext( fname, txt, quotas ) {
  if ( window.opener != null ) { 
    ed = window.opener.document.forms[0].elements[fname];
    if (ed != null) {
      r = new RegExp("x"+fname+"x", "");
      if (window.opener._accessed.search(r) == -1) {
        window.opener._accessed += fname+"x";
      }
      window.opener._active=fname;
      if (quotas == "yes") {
        var str = txt;
        str = str.replace(/&&&&&&/g, "\\\"");
        str = str.replace(/######/g, "\'");
        ed.value = "\""+str+"\"";
      } else
        ed.value = txt;
    }
  	window.close()
  }
};


var div = document.getElementById('patentBiblio');
var lineId;

var handleSuccess = function(o){
	if(o.responseText !== undefined){
		HideIndicator();

		if (o.responseText > 0)
		{
			basketHref.href = "basket.php?action=viewvasket";
			basketHref.className = "viennacat2";
			basketCount.className = "viennacat2";	
		}

		if ( o.responseText == 0)
		{
			basketHref.href = "?action=setsearchconditions";
			basketHref.className = "viennacat2not";	
			basketCount.className = "viennacat2not";	
		}
		
		basketCount.innerHTML = o.responseText;
	}
}

var handleFailure = function(o){
	if(o.responseText !== undefined){
		tblWorkingMsg.innerHTML = "<table border=0 cellspacing=0 cellpadding=0><tr><td colspan=2><br><br><br><br>";
		tblWorkingMsg.innerHTML += "<li>Error server connecting. HTTP status: " + o.status + "</li>";
		tblWorkingMsg.innerHTML += "<li>Status code message: " + o.statusText + "</li></td></tr></table>";
		HideIndicator();
	}
}

var callback =
{
  success:handleSuccess,
  failure:handleFailure,
  argument: { foo:"foo", bar:"bar" }
};

function ShowIndicator() {
	tblWorkingMsg.style.display='';
	tblWorkingMsg.style.pixelTop=(document.body.clientHeight/2)-(tblWorkingMsg.offsetHeight/2)+(document.body.scrollTop);
	tblWorkingMsg.style.pixelLeft=(document.body.clientWidth/2)-(tblWorkingMsg.offsetWidth/2)+(document.body.scrollLeft);
	//tblWorkingMsg.style.pixelTop=150;
	//tblWorkingMsg.style.pixelLeft=705;
}

function HideIndicator() {
		tblWorkingMsg.style.display='none';
	}

function basketAction(elem, dbn, idclaim)
{
	act_type = 'deletefrombasket';
	if ( elem.checked )
		act_type = 'addtobasket';

	var sUrl = "basket.php?action="+act_type+"&dbname="+dbn+"&idClaim="+idclaim;
	var request = YAHOO.util.Connect.asyncRequest('GET', sUrl, callback); 
	
	window.setTimeout("ShowIndicator()", 0);
}
