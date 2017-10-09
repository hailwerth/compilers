window.onload = function()
{
    var tempVal;
    //wire the paragraphs's on click to the function
    var allElem = document.getElementsByTagName("*");
    for(var i=0; i<allElem.length; i++)
    {
       tieFuncts(allElem[i]);
    }           
    tempVal = document.getElementById("updated");
    if(tempVal !== null) lastUpdated(tempVal);
    tempVal = document.getElementById("popUpX");
    if(tempVal !== null) tempVal.onclick = function(){ closePopUp(); };
    tempVal = document.getElementById("popUpWrap");
    if(tempVal !== null) tempVal.onclick = function(){ closePopUp(); };        
    collapseAllMenus();      
};
function tieFuncts(element)
{    
    if(element.className == "accordion-menu" && element.tagName.toLowerCase() == "p")
        element.onclick = function(){ changeMenuDisplay(this); };   
    if(element.className == "noJShide")
        element.style.display = "block";        
    if(element.className == "pub")
    {
        element.onclick = function(){ activateElem(this); };            
        element.onmouseover = function() { 
                origBC = this.style.backgroundColor; 
                this.style.backgroundColor = "#a5ebdc";                     
            };
        element.onmouseout = function() { this.style.backgroundColor = origBC; };
    }
    if(element.className == "bib" && element.tagName.toLowerCase() == "a")
        element.onclick = function(){ return bibPopUp(this); };
    if(element.className == "abstract")
    {
        element.onmouseover = function() { this.firstChild.style.display = "block"; };
        element.onmouseout = function() { this.firstChild.style.display = "none"; };
    }
}
function collapseAllMenus()
{
    var uLists = document.getElementsByTagName("ul");
    var oLists = document.getElementsByTagName("ol");
    var i;
    for(i = 0; i<uLists.length; i++)
        if(uLists[i].className == "accordion-menu")
            uLists[i].style.display="none";
    for(i = 0; i<oLists.length; i++)
        if(oLists[i].className == "accordion-menu")
            oLists[i].style.display="none";
}
function changeMenuDisplay(theParag)
{
   var listMenu = theParag.nextElementSibling;
   //unicode arrow takes only 1 space
   var htmlNoArrow = theParag.innerHTML.substring(1, theParag.innerHTML.length);
   
   //menu is collapsed (closed)
   if(listMenu.style.display == "none")
   {
        theParag.innerHTML = "&#9660;" + htmlNoArrow;          
        listMenu.style.display = "block";
   }
   else{    //menu's expanded
        theParag.innerHTML = "&#9654;" + htmlNoArrow;
        listMenu.style.display = "none";
   }           
}
function activateElem(elem)
{
    var theDiv;
    var tempVal;
    var pubSpans;
    //collapse others
    tempVal = document.getElementById("publications");
    if(tempVal !== null)
        pubSpans = tempVal.getElementsByTagName("span");
        
    for(var i = 0; i<pubSpans.length; i++)
        if(pubSpans[i].className == "pub" && pubSpans[i] != elem)
        {
            theDiv = document.getElementById("pub" + pubSpans[i].id);
            if(theDiv.className == "active")
                activateDiv(theDiv, pubSpans[i]);
        }

    theDiv = document.getElementById(elem.className + elem.id);
    if(theDiv !== null)   
        activateDiv(theDiv, elem);           
}
function activateDiv(divElem, theElem)
{
    var divElemParags;
    var i;
    if(divElem.className == "inactive")
    {
        divElem.style.display = "block";
        divElem.className = "active";
        theElem.style.color = "White";
        theElem.style.backgroundColor = '#6A0000';
        origBC = '#6A0000';        
        if(divElem.hasChildNodes())
        {
            divElemParags = divElem.getElementsByTagName("p");
            for(i = 0; i<divElemParags.length; i++)
            {
                if(divElemParags[i].className == "accordion-menu")
                    if(divElemParags[i].nextElementSibling.style.display == "none")
                        changeMenuDisplay(divElemParags[i]);
            }
        }
    }
    else
    {
        divElem.style.display = "none";
        divElem.className = "inactive";        
        theElem.style.color = "#6A0000";
        theElem.style.backgroundColor = 'Transparent';
        origBC = 'Transparent';
        //collapse menus
        if(divElem.hasChildNodes())
        {
            divElemParags = divElem.getElementsByTagName("p");
            for(i = 0; i<divElemParags.length; i++)
            {
                if(divElemParags[i].className == "accordion-menu")
                    if(divElemParags[i].nextElementSibling.style.display != "none")
                        changeMenuDisplay(divElemParags[i]);
            }
        }
    } 
}
function lastUpdated(theParag)
{
    var m = "Last updated: " + document.lastModified; 
    var p = m.length-8;   
    theParag.innerHTML = m.substring(p, 0);
}
function closePopUp()
{
    var tempVal = document.getElementById("popUpIn");
    if(tempVal !== null)
        tempVal.innerHTML = "";    
    tempVal = document.getElementById("popUpOut");
    if(tempVal !== null)
        tempVal.style.display = "none";
    tempVal = document.getElementById("popUpWrap");
    if(tempVal !== null)
        tempVal.style.display = "none";        
}
function bibPopUp(theBib)
{
    var theSrc = theBib.href;    
    
    var tempVal = document.getElementById("popUpIn");
    if(tempVal !== null)
    {
        tempVal.innerHTML = "<iframe style='background-color:white;' height='95%' width='100%' src='" + theSrc + "'></iframe>";           
        if((navigator.userAgent.indexOf("Safari") != -1) && (navigator.userAgent.indexOf("Mobile") != -1)) 
        {
          tempVal.style.overflow = "scroll";
        }
    }
    tempVal = document.getElementById("popUpOut");   
    if(tempVal !== null)
        tempVal.style.display = "block";    
    tempVal = document.getElementById("popUpWrap");
    if(tempVal !== null)
        tempVal.style.display = "block";    
    
    return false;    
}        
var origBC;
/* the accordion menu html:
<p class="accordion-menu">&#9654; </p>        
<ul class="accordion-menu">        
    <li></li>        
</ul>
*/    
