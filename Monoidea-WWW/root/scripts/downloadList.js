/**
 * the page's list id counter
 */
var listCounter = 0;

function DownloadItem(){
}

DownloadItem.prototype = new DownloadRow();

function DownloadList(p, r, i){
    super.rows = r;
    super.index = i;
    this.listId = 0;
    this.list = null;

    /**
     * @param item 
     * @param position
     * 
     * Inserts the item at the given position.
     */
    function insertItem(row, position){
	if(list === null){
	    return;
	}
	
	if(position == -1){
	    if(this.rowData === null){
		position = 0;
	    }else{
		position = this.rowData.length;
	    }
	}
	
	if(row === null){
	    row = $().extend(true, {}, this.rows);
	}
	
	/* append rowData */
	if(row.isDefaultRow){
	    this.rows = row;
	}
	
	if(!row.isDefaultRow && !row.isHeader){
	    if(this.rowData === null){
		this.rowData = [];
	    }
	    
	    this.rowData[position] = row;
	}
	
	/* fill HTML with data */
	var itemTemplate = "<li id=\"item_" + rowCounter + "\">";
	
	/* increment id-counter */
	$("#item_" + rowCounter);
	row.rowId = rowCounter;
	rowCounter++;
	
	/* iterate columns */
	var sessionIDCol = row.columns[0][SessionID];
	var tokenCol = row.columns[0][Token];
	var videoFileIDCol = row.columns[0][VideoFileID];

	itemTemplate += "<div><a href=\"http://monothek.ch/download/media?session_id=" + SessionIDCol[0].value + "&token=" + tokenCol[0].value + "&video_file_id=" + videoFileID[0].value + "\">Download your Monothek Session</a></div>";


	itemTemplate += "<div><video width=\"1280\" height=\"720\" controls><source src=\"http://monothek.ch/download/media?session_id=" + SessionIDCol[0].value + "&token=" + tokenCol[0].value + "&video_file_id=" + videoFileID[0].value + "\" type=\"video/mp4\">Your browser does not support the video tag.</video></div>";

	
	itemTemplate += "</li>";
	
	$(itemTemplate).insertAfter("#list_" + this.listId + " ul:eq(" + (position) + ")");
    }

    function createList(parent){
	var listTemplate = "<ul id=\"list_" + listCounter + "\"></ul>";
	
	if(parent === null){
	    $(document).append(listTemplate).addClass("orphan");
	}else{
	    parent.append(listTemplate);
	}
	
	/* increment id-counter */
	list = $("#list_" + listCounter);
	listCounter++;

	list.addClass("dbList");
    }

    rows = r;
    index = i;
    listId = listCounter;
    createList(p);
}

DownloadList.prototype = new AjaxTable();
