
$(document).ready(function() {

    // Инициализация корзины
    let cart = [];

    const container = $('.services-container');
    const template = $('#serviceTemplate')[0];
    const loadMoreBtn = $('#loadMoreBtn');

    const itemsPerPage = 3; // сколько показывать за раз
    let currentPage = 0;
    let allServices = [];
    let filteredServices = [];

    // элементы фильтров
    const searchNameInput = $('#searchName');
    const priceMinInput = $('#priceMin');
    const priceMaxInput = $('#priceMax');
    const resetFiltersBtn = $('#resetFilters');


    const searchInput = $('#searchName');
    const autocompleteList = $('#autocomplete-list');

    const cartWindow = $('#cart');
    let isHiddenCart = true;

    const modal = $('#checkoutModal');
    const modalContent = $('.modal-content');
    const closeModalBtn = $('#closeModal');
    const modalTotalPrice = $('#modalTotalPrice');
    const orderForm = $('#orderForm');

    showLoader();


    // загружаем JSON
    $.getJSON('data/services.json', function (data) {
        allServices = data;
        console.log(allServices);
        filteredServices = [...allServices];    // копируем

        setupAutocomplete();


        showNextItems();
        hideLoader();

        // обработчки клика по кнопке
        loadMoreBtn.on('click', function () {
            showNextItems();
        });
    }).fail(function () {
        hideLoader();
        container.append('<p>Ошибка загрузки данных.</p>');
    });

    // === обработчики событий фильтров ===

    $('.filters input').on('input', applyFilters);
    resetFiltersBtn.on('click', resetFilters);

    function applyFilters() {
        const searchName = searchNameInput.val().toLowerCase();
        const priceMin = parseInt(priceMinInput.val());
        const priceMax = parseInt(priceMaxInput.val());

        filteredServices = allServices.filter(service => {
            const nameMatch = service.name.toLowerCase().includes(searchName);
            const price = service.price;

            const priceMatch =
                (!isNaN(priceMin) ? price >= priceMin : true) &&
                (!isNaN(priceMax) ? price <= priceMax : true);

            return nameMatch && priceMatch;
        });

        // сбрасываем состояние подгрузки
        currentPage = 0;
        container.empty();
        showLoader();
        setTimeout(() => {
            hideLoader();
            showNextItems();
        }, 300);    // искусственная задержка для наглядности
    }

    function resetFilters() {
        searchNameInput.val('');
        priceMinInput.val('');
        priceMaxInput.val('');
        filteredServices = [...allServices];
        currentPage = 0;
        container.empty();
        showNextItems();
    }

    // функция отображения следующих карточек
    function showNextItems() {
        const startIndex = currentPage * itemsPerPage;
        const endIndex = startIndex + itemsPerPage;
        const pageServices = filteredServices.slice(startIndex, endIndex);

        if (pageServices.length == 0 && currentPage == 0) {
            container.append('<p style="text-align:center;">Ничего не найдено.</p>');
            loadMoreBtn.hide(); // нет данных - прячем кнопку
            return;
        } else if (pageServices.length == 0) {
            loadMoreBtn.hide();
            return;
        } else {
            loadMoreBtn.show();
        }

        pageServices.forEach((service, index) => {
            const clone = $(template.content.cloneNode(true));

            clone.find('.service').attr('id', service.id);
            clone.find('h3').text(service.name);
            clone.find('.description').eq(0).text(service.description);
            clone.find('.price').text(`Цена: ${service.price} руб.`);
            clone.find('.add-to-cart')
                .data('name', service.name)
                .data('price', service.price);
            // добавляем в контейнер
            container.append(clone);
            $(clone).find('.service').hide().fadeIn(500);
        });
        currentPage++;
    }
    // обработчик клика по кнопкам "Добавить в корзину"
    container.on('click', '.add-to-cart', function () {
        const name = $(this).data('name');
        const price = parseInt($(this).data('price'));

        cart.push({
            name: name,
            price: price
        });

        updateCart();

        // Анимация добавления
        $(this).text('Добавлено!');
        setTimeout(() => {
            $(this).text('Добавить в корзину');
        }, 1000);
    });

    function setupAutocomplete() {
        searchInput.on('input', function () {
            const query = $(this).val().toLowerCase();

            if (!query) {
                autocompleteList.empty().hide();
                return;
            }

            const matches = allServices.filter(service =>
                service.name.toLowerCase().includes(query)
            );

            autocompleteList.empty();

            if (matches.length === 0) {
                autocompleteList.append('<li>Ничего не найдено!</li>');
            } else {
                matches.forEach(service => {
                    const li = $('<li>').text(service.name);
                    li.on('click', function() {
                        searchInput.val(service.name);
                        autocompleteList.empty().hide();
                        applyFilters();
                    });
                    autocompleteList.append(li);
                });
            }

            autocompleteList.show();
        });

        // скрываем при клике вне поля
        $(document).on('click', function (e) {
            if (!$(e.target).closest('.filter-group').length) {
                autocompleteList.hide();
            }
        });
    }


    function showLoader() {
        const loader = $('<div>').addClass('loader');
        container.html(loader);
    };

    function hideLoader() {
        container.find('.loader').remove();
    }

    function updateCheckoutButton() {
        const totalPrice = parseInt($('#total-price').text());
        const checkoutBtn = $('#checkoutBtn');

        if (totalPrice > 0) {
            checkoutBtn.prop('disabled', false);
        } else {
            checkoutBtn.prop('disabled', true);
        }
    }


    // Очистка корзины
    $('#clear-cart').click(function() {
        cart = [];
        updateCart();

        // Анимация
        $(this).text('Корзина очищена!');
        setTimeout(() => {
            $(this).text('Очистить корзину');
        }, 1000);
    });

    // Обновление корзины
    function updateCart() {
        $('#cart-items').empty();
        let total = 0;

        cart.forEach(item => {
            $('#cart-items').append(`<p>${item.name} - ${item.price} руб.</p>`);
            total += item.price;
        });

        $('#total-price').text(total);

        updateCheckoutButton();

        // Анимация обновления
        $('.cart').animate({opacity: 0.4}, 200).animate({opacity: 1}, 200);
    }

    cartWindow.on('mouseenter', function () {
        if (isHiddenCart) {
            cartWindow.stop().animate({ right: '20px' }, 300);
            isHiddenCart = false;
        }
    });

    cartWindow.on('mouseleave', function() {
        if (!isHiddenCart) {
            cartWindow.stop().animate({ right: '-320px' }, 300);
            isHiddenCart = true;
        }
    });

    $('#toggleCart').on('click', function () {
        isHiddenCart = !isHiddenCart;
        cartWindow.animate(
            { right: isHiddenCart ? '-320px' : '20px' },
            300
        );
    });

    // модальное окно
    $('#checkoutBtn').on('click', function () {
        const totalPrice = parseInt($('#total-price').text());
        if (totalPrice > 0) {
            modalTotalPrice.text(totalPrice);
            modal.show();
            modalContent.css({ opacity: 0, transform: 'scale(0.8)'});
            modalContent.animate(
                { opacity: 1, transform: 'scale(1)' },
                300
            );
        }
    });

    // скрыть на крестик
    closeModalBtn.on('click', function () {
        modalContent.animate(
            { opacity: 0, transform: 'scale(0.8)' },
            250,
            function () {
                modal.hide();
                $('#orderForm')[0].reset();
            }
        )
        if ($(event.target).is(modal)) {
            modal.hide();
        }
    });

    // скрыть вне окна
    $(window).on('click', function (event) {
        if ($(event.target).is(modal)) {
            modal.hide();
        }
    })

    // Обработка отправки формы
    orderForm.on('submit', function (e) {
        e.preventDefault();

        const name = $('#clientName').val().trim();
        const phone = $('#clientPhone').val().trim();
        const address = $('#clientAddress').val().trim();
        const comment = $('#clientComment').val().trim();
        const total = modalTotalPrice.text();
        const submitBtn = $('.submit-order-btn');

        // Анимация кнопки при отправке
        submitBtn.prop('disabled', true).text('Отправка...');
        submitBtn.fadeTo(200, 0.4).fadeTo(200, 1);

        setTimeout(() => {
            $('#successMessage').fadeIn(300).delay(2000).fadeOut(300);
            alert(`Заказ оформлен!\n\nИмя: ${name}\nТелефон: ${phone}\nАдрес: ${address}\nКомментарий: ${comment}\nСумма: ${total} руб.`);

            orderForm[0].reset();       // Очистка формы
            $('#clear-cart').trigger('click'); // Очистка корзины
            modal.hide();               // Скрытие модального окна

            // Восстанавливаем кнопку
            submitBtn.text('Отправить заказ').prop('disabled', false);
        }, 1500);
    });


    // Эффект при наведении на кнопки
    $('button').hover(
        function() {
            $(this).css({
                'transform': 'scale(1.05)',
                'background-color': '#67a3d8',
                'box-shadow': '0 4px 8px rgba(0,0,0,0.2'
            });
        },
        function() {
            $(this).css({
                'transform': 'scale(1)',
                'background-color': '#2a6496',
                'box-shadow': 'none'
            });
        }
    );


});
