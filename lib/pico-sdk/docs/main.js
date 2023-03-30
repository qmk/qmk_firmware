$(document).ready(function() {

    // Trigger the mobile navigation
    $(document).on('click', '.navigation-toggle', function (event) {
        event.preventDefault();
        $(this).toggleClass('clicked');
        $('#top').toggleClass('open');
    });

    // Add a class to all <li>'s with children
    $('#main-nav ul li > ul').parent().addClass('hasChildren');
    $('#main-nav .has-submenu').removeClass('has-submenu');
    $('#main-nav .sm').removeClass('sm');
    $('#main-nav .sm-dox').removeClass('sm-dox');
    $('#main-nav #main-menu').removeAttr('data-smartmenus-id');
    $('#main-nav #main-menu').removeAttr('id');
});
