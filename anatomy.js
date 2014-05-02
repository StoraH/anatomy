(function ($) {

Drupal.behaviors.anatomy = {
  attach: function (context, settings) {

    // Get graph data
    var inputGraph = document.querySelector("#inputGraph"),

    // Parse graph data
    result = graphlibDot.parse(inputGraph.value),

    // Render graph
    renderer = new dagreD3.Renderer();
    renderer.run(result, d3.select("#anatomy g"));

  }
};

})(jQuery);
