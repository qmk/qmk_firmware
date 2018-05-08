/** global localStorage, hljs */

if (hljs) {
    hljs.initHighlightingOnLoad();
}

//Initialize CodeBlock Visibility Settings
$(function () {
    var codeBlockView = $('.Columns__right'),
        codeBlocks = $('.s-content pre'),
        toggleCodeSection = $('.CodeToggler'),
        toggleCodeBlockBtns = toggleCodeSection.find('.CodeToggler__button'),
        toggleCodeBlockBtn = toggleCodeSection.find('.CodeToggler__button--main'),
        toggleCodeBlockBtnHide = toggleCodeSection.find('.CodeToggler__button--hide'),
        toggleCodeBlockBtnBelow = toggleCodeSection.find('.CodeToggler__button--below'),
        toggleCodeBlockBtnFloat = toggleCodeSection.find('.CodeToggler__button--float');

    // If there is no code block we hide the link
    if (!codeBlocks.size()) {
        toggleCodeSection.addClass('Hidden');
        return;
    }

    function setCodeBlockStyle(codeBlockState) {
        localStorage.setItem("codeBlockState", codeBlockState);

        toggleCodeBlockBtns.removeClass("Button--active");

        switch (codeBlockState) {
            case 2: // Show code blocks inline
                toggleCodeBlockBtnFloat.addClass("Button--active");
                codeBlockView.addClass('Columns__right--float');
                codeBlockView.removeClass('Columns__right--full');
                codeBlocks.removeClass('Hidden');
                break;
            case 1: // Show code blocks below
                toggleCodeBlockBtnBelow.addClass("Button--active");
                toggleCodeBlockBtn.prop('checked', true);
                codeBlockView.removeClass('Columns__right--float');
                codeBlockView.addClass('Columns__right--full');
                codeBlocks.removeClass('Hidden');
                break;
            case 0: // Hidden code blocks
            default:
                toggleCodeBlockBtnHide.addClass("Button--active");
                toggleCodeBlockBtn.prop('checked', false);
                codeBlockView.removeClass('Columns__right--float');
                codeBlockView.addClass('Columns__right--full');
                codeBlocks.addClass('Hidden');
                break;
        }
    }

    toggleCodeBlockBtn.click(function() {
        setCodeBlockStyle(codeBlocks.hasClass('Hidden') ? 1 : 0);
    });

    toggleCodeBlockBtnHide.click(function() { setCodeBlockStyle(0); });
    toggleCodeBlockBtnBelow.click(function() { setCodeBlockStyle(1); });
    toggleCodeBlockBtnFloat.click(function() { setCodeBlockStyle(2); });

    var floating = $(document.body).hasClass("with-float");
    var codeBlockState = localStorage.getItem("codeBlockState");

    if (!codeBlockState) {
        codeBlockState = floating? 2 : 1;
    } else {
        codeBlockState = parseInt(codeBlockState);
    }

    if (!floating && codeBlockState == 2) {
        codeBlockState = 1;
    }

    setCodeBlockStyle(codeBlockState);
});


$(function () {
    // Tree navigation
    $('.aj-nav').click(function (e) {
        e.preventDefault();
        $(this).parent().siblings().find('ul').slideUp();
        $(this).next().slideToggle();
    });

    // New Tree navigation
    $('ul.Nav > li.has-children > a > .Nav__arrow').click(function() {
        $(this).parent().parent().toggleClass('Nav__item--open');
        return false;
    });

    // Responsive navigation
    $('.Collapsible__trigger').click(function () {
        $('.Collapsible__content').slideToggle();
    });
});

