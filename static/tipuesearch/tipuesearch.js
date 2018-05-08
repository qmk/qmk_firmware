/*
 Tipue Search 5.0
 Copyright (c) 2015 Tipue
 Tipue Search is released under the MIT License
 http://www.tipue.com/search
 */


(function ($) {

    var originalTitle = document.title;

    // Stop words (list from http://www.ranks.nl/stopwords)
    var tipuesearch_stop_words = ["a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during", "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their", "theirs", "them", "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours", "yourself", "yourselves"];

    // Internal strings
    var tipuesearch_string_one_result = '1 result';
    var tipuesearch_string_results = 'results';
    var tipuesearch_string_prev = 'Previous';
    var tipuesearch_string_next = 'Next';
    var tipuesearch_string_no_results = 'Nothing found';
    var tipuesearch_string_common_words_ignored = 'Common words are largely ignored';
    var tipuesearch_string_too_short = 'Search too short';
    var tipuesearch_string_one_character_or_more = 'Should be one character or more';
    var tipuesearch_string_should_be_x_or_more = 'Should be !min characters or more';

    // Main containers
    var tipue_container, tipue_backdrop;

    function getURLP(name) {
        return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(location.search) || [, ""])[1].replace(/\+/g, '%20')) || null;
    }

    function closeSearch() {
        document.title = originalTitle;

        $(document).off("keyup", keyUpHandler);

        $("body").removeClass("with-search");
        tipue_container.hide();
        tipue_backdrop.hide();
    }

    function keyUpHandler(e) {
        if (e.which == 27) { //escape
            closeSearch();
        }
    }

    function getSearchString(searchFor) {
        var standard = true;
        var hasStopWords = false;
        if ((searchFor.match("^\"") && searchFor.match("\"$")) || (searchFor.match("^'") && searchFor.match("'$"))) {
            standard = false;
        }

        if (standard) {
            var d_w = searchFor.split(' ');
            searchFor = '';
            for (var i = 0; i < d_w.length; i++) {
                var isStopWord = false;
                for (var f = 0; f < tipuesearch_stop_words.length; f++) {
                    if (d_w[i] == tipuesearch_stop_words[f]) {
                        isStopWord = true;
                        hasStopWords = true;
                    }
                }
                if (!isStopWord) {
                    searchFor = searchFor + ' ' + d_w[i];
                }
            }
            searchFor = $.trim(searchFor);
        } else {
            searchFor = searchFor.substring(1, searchFor.length - 1);
        }

        return {
            hasStopWords: hasStopWords,
            isStandard: standard,
            searchFor: searchFor
        };
    }

    function getScore(searchFor, page) {
        var score = 0;
        var pat = new RegExp(searchFor, 'gi');

        if (page.title.search(pat) != -1) {
            score += (20 * page.title.match(pat).length);
        }

        if (page.text.search(pat) != -1) {
            score += (20 * page.text.match(pat).length);
        }

        if (page.tags.search(pat) != -1) {
            score += (10 * page.tags.match(pat).length);
        }

        if (page.url.search(pat) != -1) {
            score += 20;
        }

        return score;
    }

    function makeResult(score, page, text) {
        return {
            "score": score,
            "title": page.title,
            "desc": text,
            "url": page.url
        }
    }

    window.tipuesearch = function (options) {
        var settings = $.extend(
            {
                'field': $('#tipue_search_input'),
                'show': 10,
                'showURL': true,
                'showTitleCount': true,
                'minimumLength': 3,
                'descriptiveWords': 25,
                'highlightTerms': true,
                'highlightEveryTerm': false,
                'contentLocation': 'tipuesearch/tipuesearch_content.json',
                'debug': false
            }, options);

        var tipuesearch_in = {
            pages: []
        };

        $.ajax(
            {
                dataType: "json",
                url: settings.base_url + settings.contentLocation,
                async: false
            })
            .done(
                function (json) {
                    tipuesearch_in = $.extend({}, json);
                });


        if (getURLP('q')) {
            settings.field.val(getURLP('q'));
            getTipueSearch(0, true);
        }

        settings.field.keyup(
            function (event) {
                if (event.keyCode == '13') {
                    getTipueSearch(0, true);
                }
            });


        function highlightText(search, text) {
            if (settings.highlightTerms) {
                var pattern = new RegExp('(' + search + ')', settings.highlightEveryTerm ? 'gi' : 'i');
                text = text.replace(pattern, "<span class=\"SearchResults__highlight\">$1</span>");
            }

            return text;
        }

        function getResults(searchFor, standard) {
            var found = [];

            if (standard) {
                var d_w = searchFor.split(' ');
                for (var i = 0; i < tipuesearch_in.pages.length; i++) {
                    var score = 0;
                    var text = tipuesearch_in.pages[i].text;
                    for (var f = 0; f < d_w.length; f++) {
                        if (d_w[f].match('^-')) {
                            var pat = new RegExp(d_w[f].substring(1), 'i');
                            if (tipuesearch_in.pages[i].title.search(pat) != -1 || tipuesearch_in.pages[i].text.search(pat) != -1 || tipuesearch_in.pages[i].tags.search(pat) != -1) {
                                score = 0;
                            }
                        } else {
                            score += getScore(d_w[f], tipuesearch_in.pages[i]);
                            text = highlightText(d_w[f], text);
                        }
                    }

                    if (score != 0) {
                        found.push(makeResult(score, tipuesearch_in.pages[i], text));
                    }
                }
            } else {
                for (var i = 0; i < tipuesearch_in.pages.length; i++) {
                    var score = getScore(searchFor, tipuesearch_in.pages[i]);
                    if (score != 0) {
                        found.push(makeResult(score, tipuesearch_in.pages[i], highlightText(searchFor, tipuesearch_in.pages[i].text)));
                    }
                }
            }

            found.sort(function (a, b) {
                return b.score - a.score
            });

            return found
        }

        function getTipueSearch(start, replace) {

            if (!tipue_container) {
                tipue_container = $(document.createElement("div"));
                tipue_container.addClass('SearchResults');
                document.body.appendChild(tipue_container.get(0));

                tipue_backdrop = $(document.createElement("div"));
                tipue_backdrop.addClass("SearchResultsBackdrop");
                document.body.appendChild(tipue_backdrop.get(0));

                tipue_container.on('click', '.SearchResults__close', closeSearch);
                tipue_container.on('click', '.SearchResults__footer__link', function () {
                    var id_v = $(this).attr('id');
                    var id_a = id_v.split('_');

                    getTipueSearch(parseInt(id_a[0]), id_a[1]);

                    tipue_container.scrollTop(0);
                });

                tipue_container.on('keyup paste', '.Search__field', function(event) {
                    settings.field.val($(this).val());

                    if (event.keyCode == '13') {
                        getTipueSearch(0, true);
                    }
                })
            }

            $(document).keyup(keyUpHandler);

            var output = '<input class="Search__field" placeholder="Search..." autocomplete="on" autosave="text_search" type="search" value="'+ settings.field.val() +'"><button class=SearchResults__close>&times;</button>';

            var search = getSearchString($.trim(settings.field.val().toLowerCase()));
            var searchFor = search.searchFor;

            if (searchFor.length >= settings.minimumLength) {
                var found = getResults(search.searchFor, search.isStandard);
                var counter = found.length;


                if (counter == 0) {
                    output += '<div class=SearchResults__warning>' + tipuesearch_string_no_results + '</div>';
                } else  {
                    if (settings.showTitleCount) {
                        document.title = '(' + counter + ') ' + originalTitle;
                    }

                    if (counter == 1) {
                        output += '<div class="SearchResults__count">' + tipuesearch_string_one_result + '</div>';
                    } else {
                        output += '<div class="SearchResults__count">' + counter + ' ' + tipuesearch_string_results + '</div>';
                    }

                    var l_o = 0;
                    for (var i = 0; i < found.length; i++) {
                        if (l_o >= start && l_o < settings.show + start) {
                            output += '<div class="SearchResults__title"><a href="' + settings.base_url + found[i].url + '"' + '>' + found[i].title + '</a></div>';

                            if (settings.debug) {
                                output += '<div class="SearchResults__debug">Score: ' + found[i].score + '</div>';
                            }

                            if (settings.showURL) {
                                var s_u = found[i].url.toLowerCase();
                                if (s_u.indexOf('http://') == 0) {
                                    s_u = s_u.slice(7);
                                }
                                output += '<div class="SearchResults__url"><a href="' + settings.base_url + found[i].url + '"' + '>' + s_u + '</a></div>';
                            }

                            if (found[i].desc) {
                                var t = found[i].desc;
                                var t_d = '';
                                var t_w = t.split(' ');
                                if (t_w.length < settings.descriptiveWords) {
                                    t_d = t;
                                } else {
                                    for (var f = 0; f < settings.descriptiveWords; f++) {
                                        t_d += t_w[f] + ' ';
                                    }
                                }
                                t_d = $.trim(t_d);
                                if (t_d.charAt(t_d.length - 1) != '.') {
                                    t_d += ' ...';
                                }
                                output += '<div class="SearchResults__text">' + t_d + '</div>';
                            }
                        }
                        l_o++;
                    }

                    if (counter > settings.show) {
                        var pages = Math.ceil(counter / settings.show);
                        var page = (start / settings.show);
                        output += '<div class="SearchResults__footer"><ul class="SearchResults__footer__links Pager">';

                        if (start > 0) {
                            output += '<li class="Pager--prev"><a class="SearchResults__footer__link" id="' + (start - settings.show) + '_' + replace + '">' + tipuesearch_string_prev + '</a></li>';
                        }

                        if (page <= 2) {
                            var p_b = pages;
                            if (pages > 3) {
                                p_b = 3;
                            }
                            for (var f = 0; f < p_b; f++) {
                                if (f == page) {
                                    output += '<li class="current">' + (f + 1) + '</li>';
                                } else {
                                    output += '<li><a class="SearchResults__footer__link" id="' + (f * settings.show) + '_' + replace + '">' + (f + 1) + '</a></li>';
                                }
                            }
                        } else {
                            var p_b = page + 2;
                            if (p_b > pages) {
                                p_b = pages;
                            }
                            for (var f = page - 1; f < p_b; f++) {
                                if (f == page) {
                                    output += '<li class="current">' + (f + 1) + '</li>';
                                } else {
                                    output += '<li><a class="SearchResults__footer__link" id="' + (f * settings.show) + '_' + replace + '">' + (f + 1) + '</a></li>';
                                }
                            }
                        }

                        if (page + 1 != pages) {
                            output += '<li class="Pager--next"><a class="SearchResults__footer__link" id="' + (start + settings.show) + '_' + replace + '">' + tipuesearch_string_next + '</a></li>';
                        }

                        output += '</ul></div>';
                    }
                }
            } else {
                if (search.hasStopWords) {
                    output += '<div class=SearchResults__warning>' + tipuesearch_string_no_results + '. ' + tipuesearch_string_common_words_ignored + '</div>';
                } else {
                    output += '<div class=SearchResults__warning>' + tipuesearch_string_too_short + '</div>';
                    if (settings.minimumLength == 1) {
                        output += '<div class=SearchResults__warning>' + tipuesearch_string_one_character_or_more + '</div>';
                    } else {
                        output += '<div class=SearchResults__warning>' + tipuesearch_string_should_be_x_or_more.replace("!min", settings.minimumLength) + '</div>';
                    }
                }
            }

            $("body").addClass("with-search").scrollTop(0);
            tipue_backdrop.show();
            tipue_container.scrollTop(0);
            tipue_container.show().html(output);
        }

    };

})(jQuery);
