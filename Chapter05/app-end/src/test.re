let random: unit => float = [%raw
  {|
  function() {
   return Math.random();
  }
|}
];
