document.addEventListener('DOMContentLoaded', function() {
    let timeout;
    const cityInput = document.getElementById('city-input');
    const autocompleteList = document.getElementById('autocomplete-list');

    if (cityInput && autocompleteList) {
        cityInput.addEventListener('input', function() {
            clearTimeout(timeout);
            timeout = setTimeout(() => {
                const input = this.value.trim();
                const autocompleteList = document.getElementById('autocomplete-list');

                if (input.length < 2) {
                    autocompleteList.style.display = 'none';
                    return;
                }

                fetch('scripts/search_cities.php?query=' + encodeURIComponent(input))
                    .then(response => response.json())
                    .then(data => {
                        if (data.length > 0) {
                            autocompleteList.innerHTML = '';
                            data.forEach(city => {
                                const item = document.createElement('div');
                                item.textContent = city;
                                item.addEventListener('click', function() {
                                    document.getElementById('city-input').value = city;
                                    autocompleteList.style.display = 'none';
                                });
                                autocompleteList.appendChild(item);
                            });
                            autocompleteList.style.display = 'block';
                        } else {
                            autocompleteList.style.display = 'none';
                        }
                    })
                    .catch(error => console.error('Ошибка:', error));
            }, 300);
        });

        document.addEventListener('click', function(e) {
            if (e.target.id !== 'city-input') {
                document.getElementById('autocomplete-list').style.display = 'none';
            }
        });
    }
});
