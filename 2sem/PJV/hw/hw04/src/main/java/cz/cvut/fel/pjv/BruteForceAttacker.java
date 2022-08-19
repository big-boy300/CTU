package cz.cvut.fel.pjv;

public class BruteForceAttacker extends Thief {
    private int password_len;
    private int symbol_bank_len;
    
    @Override
    public void breakPassword(int sizeOfPassword) {
        this.password_len = sizeOfPassword;
        char[] symbol_bank = getCharacters();
        symbol_bank_len = symbol_bank.length;
        String password_try = "";
        int password_len_const = password_len;

        findPassword(symbol_bank, password_try, symbol_bank_len, password_len, password_len_const);
    }

    private void findPassword(char[] symbol_bank, String password, 
                              int symbol_bank_len, int password_len, int password_len_const)
    {                
        if(password_len_const == 0){
            tryOpen("".toCharArray());      
        }
        
        if(isOpened()){
            return;
        }
        
        if(password_len == 0){
            return;
        }                                
        
        for(int i = 0; i < symbol_bank_len; ++i){
            String password_trial = password + symbol_bank[i];
            int new_password_len = password_trial.length();
            if(new_password_len == password_len_const){
                tryOpen(password_trial.toCharArray());
                if(isOpened())
                    return;
            }
            findPassword(symbol_bank, password_trial, symbol_bank_len, password_len - 1, password_len_const);
        }        
    }
}
