function sendMail() {
    var link = "mailto:surendrangokul55@gmail.com"
             + "?cc="+encodeURIComponent(document.getElementById('email').value)
             + "&subject=" + encodeURIComponent(document.getElementById('subject').value)
             + "&body=" + encodeURIComponent(document.getElementById('Message').value)
    ;
    
    window.location.href = link;
}