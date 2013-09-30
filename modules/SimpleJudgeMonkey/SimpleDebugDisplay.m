
function SimpleDebugDisplay(in_params, mm_ip)
%
% params = {message, field, dim}    
%    

    %dbstop if error;

    global RTMA;
    global params;

    RTMAPath = getenv('RTMA'); 
    SourcePath = getenv('ROBOTSRC'); 
	CommonPath = getenv('ROBOT_COMMON');
    IncludePath = getenv('ROBOTINC'); 
    
    addpath([RTMAPath '/lang/matlab']);
	addpath([CommonPath '/Matlab']);

    RTMAConfigFile = [IncludePath '/RTMA_config.mat'];
    ConnectArgs = {0, '', RTMAConfigFile};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end
    ConnectToMMM(ConnectArgs{:})

    params = in_params;
    
    % load configuration & init display
    %c = LoadTextData( config_file);
    %config = c.config;
    config.number_of_data_points = 500;
    config.active_field = params{2};
    config.active_dims = params{3};
    config.threshold_color = [.95 .95 .95];

    Subscribe(params{1})
    
    State = InitJudgeDisplay(config);
    figure;

    disp('SimpleDebugDisplay running...');
   
    while(1)
        M = ReadMessage( 0);
        if(isempty(M))
            PlotLiveData( State, config);
            pause( 0.01);
        else
			switch( M.msg_type)

				case params{1}
                    State.data = M.data;
                    State = UpdatePlotData( State, config);
			end
        end
    end
    DisconnectFromMMM

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = InitJudgeDisplay(config)

    State = struct();
    
    N = config.number_of_data_points;
    nDims = length(config.active_dims);
    
    for d = 1 : nDims
        State.LiveData.(config.active_field){d} = zeros(1, N);

        State.LiveData.max_scale{d} = eps;
        State.LiveData.min_scale{d} = -eps;
    end
       
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function PlotLiveData(State, config)
    
    global params;
    
    dims = config.active_dims;
    nDims = length(dims);
    xN = config.number_of_data_points;

    for d = 1 : nDims
        subaxis(nDims,1,d, 'Spacing', 0.01, 'Padding', 0.02, 'Margin', 0.01);

        plot(State.LiveData.(config.active_field){d}, 'k');

        xlim([1 xN]); 
        dim_idx = config.active_dims(d);
        %ylim([config.min_scale(dim_idx) config.max_scale(dim_idx)]);
        %ylim([config.min_scale config.max_scale]);
        ylim([State.LiveData.min_scale{d} State.LiveData.max_scale{d}]);
        yLimG = get( gca, 'YLim'); 
        
        set(gca,'XTick',[]);
        title(sprintf('Dim %d', dims(d)));
    end  
    legend_str = [strrep(params{1},'_','\_') '   ' strrep(params{2},'_','\_') '  (' num2str(params{3}) ')'];
    legend({legend_str}, 'Location', 'SouthOutside', 'Orientation', 'horizontal');

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = UpdatePlotData( State, config)

    dims = config.active_dims;
    nDims = length(dims);
    
    for d = 1 : nDims
        dim_idx = dims(d);
        field_data = State.data.(config.active_field)(dim_idx);

        % insert new data to plotting arrays
        State.LiveData.(config.active_field){d} = AddDataToWindowedArray(State.LiveData.(config.active_field){d}, field_data);

        min_data = min(State.LiveData.(config.active_field){d});
        if ( min_data < State.LiveData.min_scale{d})
            State.LiveData.min_scale{d} = min_data;
        end

        max_data = max(State.LiveData.(config.active_field){d});
        if ( max_data > State.LiveData.max_scale{d})
            State.LiveData.max_scale{d} = max_data;
        end

    end

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function Array = AddDataToWindowedArray(Array, data)
    Array(end+1) = data;
    Array(1) = [];

    
