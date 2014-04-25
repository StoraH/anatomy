(function ($) {

Drupal.behaviors.anatomy = {
  attach: function (context, settings) {

    // create an array with nodes
    var nodes = settings.anatomy.nodes;

    // create an array with edges
    var edges = settings.anatomy.edges;

    var container = document.getElementById('anatomy');
    var data = {
      nodes: nodes,
      edges: edges,
    };

    var options = {
      width:  '100%',
      height: '600px',
      edges: {
        // color: 'red',
        width: 2
      },
      smoothCurves: false,
    };

    var timeline = new vis.Graph(container, data, options);


  }
};

})(jQuery);
