#�и��ͼһ������

BEGIN{
    min_x = 510
    max_x = 1622
    min_y = 580
    max_y = 1770
}
{
    street_name = $1
    type  = $2
    x1 = $3
    y1 = $4
    x2 = $5
    y2 = $6

    cutLine()

}
END {



}

function  keepInArea () 
{
    # �ص������� ����������
    if ( min_x >int( x1) ) {
	x1 = min_x
    } else if ( max_x < int(x1) ) {
	x1 = max_x 
    }

    if ( min_x > int(x2) ) {
	x2 = min_x
    } else if ( max_x < int(x2) ) {
	x2 = max_x 
    }

    if ( min_y > int(y1) ) {
	y1  = min_y 
    } else if ( max_y < int(y1) ) {
	y1  = max_y 
    }

    if ( min_y >int(  y2 ) ) {
	y2  = min_y 
    } else if ( max_y < int ( y2) ) {
	y2  = max_y 
    }

   print street_name, type, x1,  y1,  x2 ,  y2
}

function cutLine ()
{
   
    if ( min_x < int(x1) && int(x1) < max_x  && min_y < int(y1) && int( y1) < max_y  ) {
	if  ( min_x < int(x2)  && int(x2) < max_x  && min_y <int( y2) && int( y2) < max_y  ) {
	    # ������
	    print $0 
	} else {
	    #�������ཻ
	    keepInArea () 
	}
    } else if   ( min_x < int(x2)  && int(x2) < max_x  && min_y <int( y2) && int( y2) < max_y  ) {
	# �������ཻ
	keepInArea () 
    } else {

    } 
	
}

