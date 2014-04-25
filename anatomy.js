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
      smoothCurves: false,
      stabilize: false,

      nodes: {
        radiusMin: 16,
        radiusMax: 32,
        fontColor: 'BLACK'
      },

      edges: {
        color: 'GRAY'
      },

      physics: {
          barnesHut: {
              enabled: true,
              gravitationalConstant: -2000,
              centralGravity: 0.1,
              springLength: 95,
              springConstant: 0.04,
              damping: 0.09
          },
          repulsion: {
              centralGravity: 0.1,
              springLength: 50,
              springConstant: 0.05,
              nodeDistance: 100,
              damping: 0.09
          },
      }



    };

    var timeline = new vis.Graph(container, data, options);


  }
};

})(jQuery);
