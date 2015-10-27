<script>
  var elements = document.querySelectorAll(".toggleshow"),
      hideClass = 'toggleshow-hide';

  for (var i = 0; i < elements.length; i++) {
    var arrow = elements[i].querySelector(".toggleshow-arrow");
    // Initial hide/show based on class
    // Update arrow as well
    if (containsClass(elements[i], 'toggleshow-hide')) {
      toggleDisplay(elements[i]);
      changeArrow(arrow, false);
    } else {
      changeArrow(arrow, true);
    }

    // Add click handler
    addClick(elements[i], toggleDisplay);
  }

  function containsClass(element, className) {
    var eleClassName = ' ' + elements[i].className + ' ';
    return eleClassName.indexOf(' ' + className + ' ') > -1;
  }

  function toggleDisplay(parentElement) {
    var body = parentElement.querySelector(".toggleshow-body"),
        arrow = parentElement.querySelector(".toggleshow-arrow");

    if (body.style.display == 'block' || body.style.display == '') {
      body.style.display = 'none';
      changeArrow(arrow, false);
    } else {
      body.style.display = 'block';
      changeArrow(arrow, true);
    }
  }

  function changeArrow(element, visible) {
    if (visible) {
      element.innerHTML = '&#9650';
    } else {
      element.innerHTML = '&#9660';
    }
  }

  function addClick(parentElement, func) {
    parentElement.querySelector(".toggleshow-title").addEventListener("click", function(e) {
      func(parentElement);
      e.preventDefault();
      return false;
    });
  }
</script>
