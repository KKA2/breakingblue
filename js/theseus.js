/*
    Theseus
    index.html
    Ann Keenan
        Kate Barlock, Katricia Herring
*/
$(document).ready(function() {
    // adjust navigation bar based on scroll position
    $('body').scrollspy({
        target: '.navbar-fixed-top'
    });

    $(document).ready(function () {
        $(".navbar-nav li a").click(function(event) {
            $(".navbar-collapse").collapse('hide');
        });
    });

    var code;
    $('#submit').click(function() {
        // store contents of text field
        code = ($('#book-code').val());
        // hard coding of two potential options
        if (code == 'E 743.5 .H43 2011') {
            $('#book-floor').text('Floor 10');
            $('#book-floor-image').attr("src","./img/whats-fair-on-the-air.jpg");
            $('#book-title').text('What\'s Fair On The Air?');
            $('#book-author').text('Heather Hendershot');
        }
        else if (code == 'E 208 .M85 2012') {
            $('#book-floor').text('Floor 10');
            $('#book-floor-image').attr("src","./img/the-rise-of-the-republic.jpg");
            $('#book-title').text('The Birth of the Republic');
            $('#book-author').text('Edmund S. Morgan');
        }
        else {
            // reset/hide all images/text
            $('#book-floor-image').attr("src","img/campus-map.jpg");
            $("#book-floor").addClass("hidden");
            $("#book-info").addClass("hidden");
            alert('Book not available');
            return false;
        }
        // display all hidden text
        $("#book-floor").removeClass("hidden");
        $("#book-info").removeClass("hidden");
        // scroll to map
        smoothScroll.animateScroll('#map');
        return false;
    });

});
