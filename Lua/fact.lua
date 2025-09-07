function Fact(n)
  if n < 2 then
    return 1;
  else
    return n * Fact(n - 1);
  end
end
