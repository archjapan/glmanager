(function($){ 
  $('#page1').live('pagecreate', function() {
    console.log('page1.pagecreate');
    var socket = io.connect('http://'+location.hostname+':'+location.port);
    socket.on('news', function (data) {
      console.log(data);
      socket.emit('my other event', { my: 'data' });
    });
	
	$('#primitive').live('tap', function() {
	  console.log('primitive');
	  var prim = $('#primitive .ui-btn-active').attr('gl-primitive');
	  socket.emit('glManager', 'PRIM '+prim);
	});
	
	$('#size-selector').bind('change', function(e,ui) {
	  console.log('a');
	});
	
	$('#move-switch').bind('change', function(e,ui) {
	  console.log('move-switch');
	  socket.emit('glManager', 'MOVE '+ $('#move-switch')[0].value);
	});

        var pos_x = 0.0, pos_y = 0.0;
        window.addEventListener("devicemotion", function(e) {
          try
          {
            if(e)
            {
              var pos = e.accelerationIncludingGravity;
              var filter_val = 0.1;
              var accel_scale = 80.0;

              pos_x = (pos.x * accel_scale * filter_val) + (pos_x * (1.0 - filter_val));
              pos_y = (-pos.y * accel_scale * filter_val) + (pos_y * (1.0 - filter_val));
              //socket.volatile.emit('glManager', 'GRAVITY '+pos_x+' '+pos_y);
              var str = 'GRAVITY '+pos_x+' '+pos_y;
              console.log(str);
              socket.emit('glManager', 'GRAVITY '+pos_x+' '+pos_y);
            }
          }catch(e){
            console.log(e);
          }
        }, true);
  });
})(jQuery);
