%%
% filename = 'bothtc2.inp';
% filename = 'a_noise2.inp';

d = dir('*.inp')

for jj = 1:length(d)

    filename = d(jj).name
    % filename = 'bothtc2.inp';
%     filename = 'a_noise2.inp';
    checkInputs(filename);
    fileBase = strrep(filename,'.inp','')
    load ([fileBase '.mat']);
    rgt =[]; lft =[]; t =[];
    % get the highest node of each input frequency of right side
    for ii = 1:length(mgnId);
        if (isempty(mgnId(ii).node(:)))
            rgt(ii) = 0;
        else
            rgt(ii) = max(mgnId(ii).node(:));
        end
    end
    % same for left
    for ii = 1:length(gmgnId);
        if (isempty(gmgnId(ii).node(:)))
            lft(ii) = 0;
        else
            lft(ii) = max(gmgnId(ii).node(:));
        end
    end
    t = cumsum(runVals);

     ln = max([length(mgnId) length(gmgnId) length(t)]);
     if (isempty(t)); t = zeros(1,ln);end
      
    
    fig = figure;
    subplot(2,1,1); hold on; title(upper(strrep(fileBase,'_',' '))); plot(t(1:length(rgt)),rgt,'r');
    subplot(2,1,2);plot(t(1:length(lft)),lft,'b')

    saveas(fig,[filename(1:end-4) '.fig'])
% close(fig)
end