<?echo '<?xml version="1.0" encoding="utf-8"?>';?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
          "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  </head>
  <body>
      
<?
dl('transliterate.so');

function out($code, $result)
{
    echo "<p><code>";
    echo $code;
    echo "</code> => ";
    echo $result;
    echo "</p>";
}
?>

<h2>
Betacode Greek
</h2>

<?out("lo/gos", betacode_greek_to_utf8("lo/gos"));?>
<?out(")/Oida ou)de\n ei)dw/s.",
      betacode_greek_to_utf8(")/Oida ou)de\n ei)dw/s."));?>
<h2>
Betacode Hebrew
</h2>
<?out("Alhym2", betacode_hebrew_to_utf8("Alhym2"));?>

<h2>
cjhebrew
</h2>
<?out("'E:lohiym", cjhebrew_to_utf8("'E:lohiym"));?>

</body>
</html>