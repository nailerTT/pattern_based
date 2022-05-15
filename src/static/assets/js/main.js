    "use strict";

   /*--
        preloader
    -----------------------------------*/
    $(window).on('load', function(event) {
        $('#preloader').delay(500).fadeOut(500);
    });
  
    /*--
		Search
	-----------------------------------*/
	$('#search').on('click', function(event) {    
		$(".search-bar").slideToggle(500);
	});
    
    /*--
        Header Sticky
    -----------------------------------*/
    window.onscroll = function () {
        const left = document.getElementById("header");

        if (left.scrollTop > 50 || self.pageYOffset > 50) {
            left.classList.add("sticky")
        } else {
            left.classList.remove("sticky");
        }
    }  

     /*--    
        Tabs
    -----------------------------------*/  
    const tabs = document.querySelectorAll('[data-tab-target]')
    const tabContents = document.querySelectorAll('.corpix-marketing-tab-pane')

    tabs.forEach(tab => {
        tab.addEventListener('click', () => {
            const target = document.querySelector(tab.dataset.tabTarget)
            tabContents.forEach(tabContent => {
                tabContent.classList.remove('active')
            })
            tabs.forEach(tab => {
                tab.classList.remove('active')
            })
            tab.classList.add('active')
            target.classList.add('active')
        })
    })

    $('.corpix-marketing-title').click(function(e) {
        e.preventDefault();
    
    let $this = $(this);
    
    if ($this.next().hasClass('show')) {
        $this.next().removeClass('show');
        $this.next().slideUp(350);
    } else {
        $this.parent().parent().find('corpix-marketing-body').removeClass('show');
        $this.parent().parent().find('corpix-marketing-body').slideUp(350);
        $this.next().toggleClass('show');
        $this.next().slideToggle(350);
    }
    });



    /*--
        Menu parent Element Icon
    -----------------------------------*/
    const $subMenu = document.querySelectorAll('.sub-menu');
    $subMenu.forEach(function (subMenu) {
        const menuExpand = document.createElement('span')
        menuExpand.classList.add('menu-icon')
        // menuExpand.innerHTML = '+'
        subMenu.parentElement.insertBefore(menuExpand, subMenu)
        if (subMenu.classList.contains('mega-menu')) {
            subMenu.classList.remove('mega-menu')
            subMenu.querySelectorAll('ul').forEach(function (ul) {
                ul.classList.add('sub-menu')
                const menuExpand = document.createElement('span')
                menuExpand.classList.add('menu-icon')
                menuExpand.innerHTML = '+'
                ul.parentElement.insertBefore(menuExpand, ul)
            })
        }
    })

    
    /*--
        Mobile Menu 
    -----------------------------------*/

    /* Get Sibling */
    const getSiblings = function (elem) {
        const siblings = []
        let sibling = elem.parentNode.firstChild
        while (sibling) {
            if (sibling.nodeType === 1 && sibling !== elem) {
                siblings.push(sibling)
            }
            sibling = sibling.nextSibling
        }
        return siblings
    }

    /* Slide Up */
    const slideUp = (target, time) => {
        const duration = time ? time : 500;
        target.style.transitionProperty = 'height, margin, padding'
        target.style.transitionDuration = duration + 'ms'
        target.style.boxSizing = 'border-box'
        target.style.height = target.offsetHeight + 'px'
        target.offsetHeight
        target.style.overflow = 'hidden'
        target.style.height = 0
        window.setTimeout(() => {
            target.style.display = 'none'
            target.style.removeProperty('height')
            target.style.removeProperty('overflow')
            target.style.removeProperty('transition-duration')
            target.style.removeProperty('transition-property')
        }, duration)
    }

    /* Slide Down */
    const slideDown = (target, time) => {
        const duration = time ? time : 500;
        target.style.removeProperty('display')
        let display = window.getComputedStyle(target).display
        if (display === 'none') display = 'block'
        target.style.display = display
        const height = target.offsetHeight
        target.style.overflow = 'hidden'
        target.style.height = 0
        target.offsetHeight
        target.style.boxSizing = 'border-box'
        target.style.transitionProperty = 'height, margin, padding'
        target.style.transitionDuration = duration + 'ms'
        target.style.height = height + 'px'
        window.setTimeout(() => {
            target.style.removeProperty('height')
            target.style.removeProperty('overflow')
            target.style.removeProperty('transition-duration')
            target.style.removeProperty('transition-property')
        }, duration)
    }

    /* Slide Toggle */
    const slideToggle = (target, time) => {
        const duration = time ? time : 500;
        if (window.getComputedStyle(target).display === 'none') {
            return slideDown(target, duration)
        } else {
            return slideUp(target, duration)
        }
    }


    /*--
		Offcanvas/Collapseable Menu 
	-----------------------------------*/
    const offCanvasMenu = function (selector) {

        const $offCanvasNav = document.querySelector(selector),
            $subMenu = $offCanvasNav.querySelectorAll('.sub-menu');
        $subMenu.forEach(function (subMenu) {
            const menuExpand = document.createElement('span')
            menuExpand.classList.add('menu-expand')
            // menuExpand.innerHTML = '+'
            subMenu.parentElement.insertBefore(menuExpand, subMenu)
            if (subMenu.classList.contains('mega-menu')) {
                subMenu.classList.remove('mega-menu')
                subMenu.querySelectorAll('ul').forEach(function (ul) {
                    ul.classList.add('sub-menu')
                    const menuExpand = document.createElement('span')
                    menuExpand.classList.add('menu-expand')
                    menuExpand.innerHTML = '+'
                    ul.parentElement.insertBefore(menuExpand, ul)
                })
            }
        })

        $offCanvasNav.querySelectorAll('.menu-expand').forEach(function (item) {
            item.addEventListener('click', function (e) {
                e.preventDefault()
                const parent = this.parentElement
                if (parent.classList.contains('active')) {
                    parent.classList.remove('active');
                    parent.querySelectorAll('.sub-menu').forEach(function (subMenu) {
                        subMenu.parentElement.classList.remove('active');
                        slideUp(subMenu)
                    })
                } else {
                    parent.classList.add('active');
                    slideDown(this.nextElementSibling)
                    getSiblings(parent).forEach(function (item) {
                        item.classList.remove('active')
                        item.querySelectorAll('.sub-menu').forEach(function (subMenu) {
                            subMenu.parentElement.classList.remove('active');
                            slideUp(subMenu)
                        })
                    })
                }
            })
        })
    }
    offCanvasMenu('.offcanvas-menu');


    /*--    
        Brand Active
    -----------------------------------*/
    var swiper = new Swiper(".brand-active .swiper-container", {
        slidesPerView: 5,
        spaceBetween: 30,
        loop: true,
        breakpoints: {
          0: {
            slidesPerView: 1,
          },
          576: {
            slidesPerView: 2,
            spaceBetween: 20,
          },
          768: {
            slidesPerView: 3,
          },
          992: {
            slidesPerView: 5,
          },
        },
    });
    

    /*--    
        Team Active
    -----------------------------------*/
    var swiper = new Swiper(".team-active", {
        slidesPerView: 4,
        spaceBetween: 30,
        loop: true,
        pagination: {
            el: ".team-active .swiper-pagination",
            clickable: true,
        },
        breakpoints: {
          0: {
            slidesPerView: 1,
          },
          576: {
            slidesPerView: 2,
            spaceBetween: 20,
          },
          992: {
            slidesPerView: 3,
          },
          1200: {
            slidesPerView: 4,
          },
        },
    });

    /*--    
        Brand Active
    -----------------------------------*/
    var swiper = new Swiper(".testimonial-active", {
        slidesPerView: 1,
        spaceBetween: 30,
        loop: true,
        pagination: {
            el: ".testimonial-active .swiper-pagination",
            clickable: true,
        },
    });

    /*--    
        Work Active
    -----------------------------------*/
    var swiper = new Swiper(".work-active", {
        slidesPerView: 4,
        spaceBetween: 30,
        grabCursor: true,
        centeredSlides: true,
        loop: true,
        pagination: {
            el: ".work-active .swiper-pagination",
            clickable: true,
        },
        breakpoints: {
          0: {
            slidesPerView: 1,
          },
          576: {
            slidesPerView: 2,
            spaceBetween: 20,
          },
          992: {
            slidesPerView: 2,
          },
          1200: {
            slidesPerView: 4,
          },
        },
    });

    /*--    
      Counter Up
    -----------------------------------*/  

    $('.counter').counterUp({
        delay: 10,
        time: 1500,
    });

    /*--    
      Progress Bar
    -----------------------------------*/  

    if($('.progress-line').length) {
    $('.progress-line').appear(function(){
        var el = $(this);
        var percent = el.data('width');
        $(el).css('width', percent+'%');
    }, {accY: 0});
    }

    /*--
    magnificPopup video view 
  -----------------------------------*/	
	$('.popup-video').magnificPopup({
		type: 'iframe'
	});
 

    /*--
        AOS
    -----------------------------------*/

    AOS.init({
        duration: 1200,
        once: true,
    });


    /*--
        Back To Top
    -----------------------------------*/

    // Scroll Event
    $(window).on('scroll', function () {
        var scrolled = $(window).scrollTop();
        if (scrolled > 300) $('.back-btn').addClass('active');
        if (scrolled < 300) $('.back-btn').removeClass('active');
    });

    // Click Event
    $('.back-btn').on('click', function () {
        $("html, body").animate({
            scrollTop: "0"
        }, 1200);
    });

